#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <string>     // std::string, std::to_string

// get face point for each face
void get_face_points(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & face_points
)
{
  Eigen::RowVector3d fp;
  face_points.resize(F.rows(), 3);
  int i;
  for (i = 0; i < F.rows(); i++) {
    fp = (V.row(F(i, 0)) + V.row(F(i, 1)) + V.row(F(i, 2)) + V.row(F(i, 3))) / 4.0;
    face_points.row(i) = fp;
  }
}

void get_max_min(
  const int& a,
  const int& b,
  int& max,
  int& min
  )
{
  if (a > b) 
  {
    max = a;
    min = b;
  }
  else
  {
    max = b;
    min = a;
  }
}


void get_edges_face_map(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  std::unordered_map<std::string, std::vector<int>> & ef_map
)
{
  int i, j;
  int c0, c1, c2, c3;
  int max, min;
  std::string cur_edge;
  for (i = 0; F.rows(); i++) {
    c0 = F(i, 0);
    c1 = F(i, 1);
    c2 = F(i, 2);
    c3 = F(i, 3);

    // edge 0
    get_max_min(c0, c1, max, min);
    cur_edge = std::to_string(min) + "-" + std::to_string(max);
    ef_map[cur_edge].push_back(i);

    // edge 1
    get_max_min(c1, c2, max, min);
    cur_edge = std::to_string(min) + "-" + std::to_string(max);
    ef_map[cur_edge].push_back(i);

    // edge 2
    get_max_min(c2, c3, max, min);
    cur_edge = std::to_string(min) + "-" + std::to_string(max);
    ef_map[cur_edge].push_back(i);
    
    // edge 3
    get_max_min(c3, c0, max, min);
    cur_edge = std::to_string(min) + "-" + std::to_string(max);
    ef_map[cur_edge].push_back(i);
  }
}

void get_mid_point(
  const Eigen::RowVector3d& a,
  const Eigen::RowVector3d& b,
  Eigen::RowVector3d& mid
)
{
  mid = (a + b) / 2.0;
}


void get_vertex_face_map(
  const Eigen::MatrixXd& V,
  const Eigen::MatrixXi& F,
  std::unordered_map<int, std::vector<int>>& vf_map
)
{
  int i, j;
  int c0, c1, c2, c3;
  for (i = 0; F.rows(); i++) {
    c0 = F(i, 0);
    c1 = F(i, 1);
    c2 = F(i, 2);
    c3 = F(i, 3);

    vf_map[c0].push_back(i);
    vf_map[c1].push_back(i);
    vf_map[c2].push_back(i);
    vf_map[c3].push_back(i);
  }
}

void get_edge_point_and_map(
  const Eigen::MatrixXd& V,
  const Eigen::MatrixXi& F,
  const std::unordered_map<std::string, std::vector<int>>& ef_map,
  const Eigen::MatrixXd& face_points,
  std::vector<Eigen::RowVector3d>& edge_points,
  std::unordered_map<std::string, int>& eep_map
)
{
  std::string first_str, second_str;
  int first, second;
  std::vector<int> related_faces;
  Eigen::RowVector3d mid_point, center_face_point, cur_edge_point;
  int ind = 0;
  for (auto const& kv : ef_map) {
    first_str = (kv.first).substr(0, (kv.first).find("-"));
    first = std::stoi(first_str);
    second_str = (kv.first).substr(1, (kv.first).find("-"));
    second = std::stoi(second_str);

    related_faces = kv.second;
    assert((related_faces.size() < 2) && "Edge is having less than 2 faces.");
    assert((related_faces.size() > 2) && "Edge is having more than 2 faces.");
    assert((related_faces.size() != 2) && "Edge is not having 2 faces.");

    get_mid_point(V.row(first), V.row(second), mid_point);
    center_face_point = (face_points.row(related_faces[0]) + face_points.row(related_faces[1])) / 2.0;
    cur_edge_point = (mid_point + center_face_point) / 2.0;
    edge_points.push_back(cur_edge_point);
    eep_map[(kv.first)] = ind;
    ind++;
  }
}

void get_vertex_neighbours(
  const Eigen::MatrixXi& F,
  std::unordered_map<int, std::vector<int>>& vertex_neighbours
)
{
  int i;
  int v0, v1, v2, v3;
  int cur, n0, n1;
  for (i = 0; i < F.rows(); i++) {
    v0 = F(i, 0);
    v1 = F(i, 1);
    v2 = F(i, 2);
    v3 = F(i, 3);

    // vertex 0
    cur = v0; 
    n0 = v1; 
    n1 = v3;
    // if not found, add
    if (std::find(vertex_neighbours[cur].begin(), vertex_neighbours[cur].end(), n0) == vertex_neighbours[cur].end()) {
      vertex_neighbours[cur].push_back(n0);
    }
    if (std::find(vertex_neighbours[cur].begin(), vertex_neighbours[cur].end(), n1) == vertex_neighbours[cur].end()) {
      vertex_neighbours[cur].push_back(n1);
    }

    // vertex 1
    cur = v1;
    n0 = v0;
    n1 = v2;
    if (std::find(vertex_neighbours[cur].begin(), vertex_neighbours[cur].end(), n0) == vertex_neighbours[cur].end()) {
      vertex_neighbours[cur].push_back(n0);
    }
    if (std::find(vertex_neighbours[cur].begin(), vertex_neighbours[cur].end(), n1) == vertex_neighbours[cur].end()) {
      vertex_neighbours[cur].push_back(n1);
    }

    // vertex 2
    cur = v2;
    n0 = v1;
    n1 = v3;
    if (std::find(vertex_neighbours[cur].begin(), vertex_neighbours[cur].end(), n0) == vertex_neighbours[cur].end()) {
      vertex_neighbours[cur].push_back(n0);
    }
    if (std::find(vertex_neighbours[cur].begin(), vertex_neighbours[cur].end(), n1) == vertex_neighbours[cur].end()) {
      vertex_neighbours[cur].push_back(n1);
    }

    // vertex 3
    cur = v3;
    n0 = v2;
    n1 = v0;
    if (std::find(vertex_neighbours[cur].begin(), vertex_neighbours[cur].end(), n0) == vertex_neighbours[cur].end()) {
      vertex_neighbours[cur].push_back(n0);
    }
    if (std::find(vertex_neighbours[cur].begin(), vertex_neighbours[cur].end(), n1) == vertex_neighbours[cur].end()) {
      vertex_neighbours[cur].push_back(n1);
    }
  }
}


void get_vertex_point(
  const Eigen::MatrixXd& V,
  const Eigen::MatrixXi& F,
  const Eigen::MatrixXd& face_points,
  std::unordered_map<int, std::vector<int>>& vf_map,
  std::unordered_map<int, std::vector<int>>& vertex_neighbours,
  Eigen::MatrixXd& vertex_points
)
{
  vertex_points.resize(V.rows(), V.cols());
  int i;
  Eigen::RowVector3d old_coords, new_coords, avg_face_points, avg_mid_edges, cur_mid_point;
  double n;
  double m1, m2, m3;
  for (i = 0; i < V.rows(); i++) {
    old_coords = V.row(i);

    avg_face_points = Eigen::RowVector3d(0, 0, 0);
    for (int f : vf_map[i]) {
      avg_face_points += face_points.row(f);
    }
    n = (double)vf_map[i].size();
    avg_face_points /= n;

    avg_mid_edges = Eigen::RowVector3d(0, 0, 0);
    for (int v : vertex_neighbours[i]) {
      cur_mid_point = Eigen::RowVector3d(0, 0, 0);
      get_mid_point(V.row(i), V.row(v), cur_mid_point);
      avg_mid_edges += cur_mid_point;
    }
    avg_mid_edges /= ((double)vertex_neighbours[i].size());

    m1 = (n - 3.0) / n;
    m2 = 1.0 / n;
    m3 = 2.0 / n;
    new_coords = (m1 * old_coords) + (m2 * avg_face_points) + (m3 * avg_mid_edges);
    vertex_points.row(i) = new_coords;
  }
}


void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // https://rosettacode.org/wiki/Catmull%E2%80%93Clark_subdivision_surface

  // if this is the last iteration
  SV = V;
  SF = F;
  if ((num_iters - 1) == 0) {
    return;
  }

  // new results, need to resize
  Eigen::MatrixXd new_V;
  Eigen::MatrixXi new_F;

  // step 1, for each face, a face point is created which is the average of all the points of the face.
  Eigen::MatrixXd face_points;
  get_face_points(V, F, face_points);

  // step 2, for each edge, an edge point is created which is the average between the center of the 
  // edge and the center of the segment made with the face points of the two adjacent faces.
  std::unordered_map<std::string, std::vector<int>> ef_map;
  get_edges_face_map(V, F, ef_map);

  std::unordered_map<int, std::vector<int>> vf_map;
  get_vertex_face_map(V, F, vf_map);

  // get edge points
  std::vector<Eigen::RowVector3d> edge_points;
  std::unordered_map<std::string, int> eep_map;
  get_edge_point_and_map(V, F, ef_map, face_points, edge_points, eep_map);


  // step 3, for each vertex point, its coordinates are updated from(new_coords) :
  //  the old coordinates(old_coords),
  //  the average of the face points of the faces the point belongs to(avg_face_points),
  //  the average of the centers of edges the point belongs to(avg_mid_edges),
  //  how many faces a point belongs to(n), then use txhis formula :
  std::unordered_map<int, std::vector<int>> vertex_neighbours;
  get_vertex_neighbours(F, vertex_neighbours);

  Eigen::MatrixXd vertex_points;
  get_vertex_point(V, F, face_points, vf_map, vertex_neighbours, vertex_points);

  // last step, for the new vertices and faces
  new_V.resize(vertex_points.rows() + face_points.rows() + edge_points.size(), 3);
  int fp_buffer = vertex_points.rows();
  int ep_buffer = vertex_points.rows() + face_points.rows();
  new_F.resize(F.rows() * 4, 4);

  int i;

  // fufill new_v;
  for (i = 0; i < vertex_points.rows(); i++) {
    new_V.row(i) = vertex_points.row(i);
  }
  for (i = 0; i < face_points.rows(); i++) {
    new_V.row(i + fp_buffer) = face_points.row(i);
  }
  for (i = 0; i < edge_points.size(); i++) {
    new_V.row(i + ep_buffer) = edge_points[i];
  }

  Eigen::RowVector4i new_face;
  int ind = 0;
  int v0, v1, v2, v3;
  int cur, n0, n1, max, min;
  std::string eep_key0, eep_key1;
  for (i = 0; i < F.rows(); i++) {
    v0 = F(i, 0);
    v1 = F(i, 1);
    v2 = F(i, 2);
    v3 = F(i, 3);

    // face 0
    new_face = Eigen::RowVector4i(0, 0, 0, 0);
    cur = v0;
    n0 = v1;
    n1 = v3;

    get_max_min(cur, n0, max, min);
    eep_key0 = std::to_string(min) + "-" + std::to_string(max);
    get_max_min(cur, n1, max, min);
    eep_key1 = std::to_string(min) + "-" + std::to_string(max);
    new_face(0) = cur;
    new_face(1) = eep_map[eep_key0] + ep_buffer;
    new_face(2) = i + fp_buffer;
    new_face(3) = eep_map[eep_key1] + ep_buffer;
    new_F.row(ind) = new_face;
    ind++;

    // face 1
    new_face = Eigen::RowVector4i(0, 0, 0, 0);
    cur = v1;
    n0 = v2;
    n1 = v0;

    get_max_min(cur, n0, max, min);
    eep_key0 = std::to_string(min) + "-" + std::to_string(max);
    get_max_min(cur, n1, max, min);
    eep_key1 = std::to_string(min) + "-" + std::to_string(max);
    new_face(0) = cur;
    new_face(1) = eep_map[eep_key0] + ep_buffer;
    new_face(2) = i + fp_buffer;
    new_face(3) = eep_map[eep_key1] + ep_buffer;
    new_F.row(ind) = new_face;
    ind++;

    // face 2
    new_face = Eigen::RowVector4i(0, 0, 0, 0);
    cur = v2;
    n0 = v3;
    n1 = v1;

    get_max_min(cur, n0, max, min);
    eep_key0 = std::to_string(min) + "-" + std::to_string(max);
    get_max_min(cur, n1, max, min);
    eep_key1 = std::to_string(min) + "-" + std::to_string(max);
    new_face(0) = cur;
    new_face(1) = eep_map[eep_key0] + ep_buffer;
    new_face(2) = i + fp_buffer;
    new_face(3) = eep_map[eep_key1] + ep_buffer;
    new_F.row(ind) = new_face;
    ind++;

    // face 3
    new_face = Eigen::RowVector4i(0, 0, 0, 0);
    cur = v3;
    n0 = v0;
    n1 = v2;

    get_max_min(cur, n0, max, min);
    eep_key0 = std::to_string(min) + "-" + std::to_string(max);
    get_max_min(cur, n1, max, min);
    eep_key1 = std::to_string(min) + "-" + std::to_string(max);
    new_face(0) = cur;
    new_face(1) = eep_map[eep_key0] + ep_buffer;
    new_face(2) = i + fp_buffer;
    new_face(3) = eep_map[eep_key1] + ep_buffer;
    new_F.row(ind) = new_face;
    ind++;
  }

  // if not the last iteration, go to the next iteration
  catmull_clark(new_V, new_F, (num_iters - 1), SV, SF);
  ////////////////////////////////////////////////////////////////////////////
}
