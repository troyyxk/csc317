#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>

// get face point for each face
void get_face_points(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & face_points
)
{
  Eigen::RowVector3d fp;
  face_points.resize(F.rows, 3);
  int i;
  for (i = 0; i < F.rows(); i++) {
    fp = (V.row(F(i, 0)) + V.row(F(i, 1)) + V.row(F(i, 2)) + V.row(F(i, 3))) / 4.0;
    face_points.row(i) = fp;
  }
}


// get edges, mid points, edge face map and face edge map.
void get_edges_and_related(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  std::vector<std::pair> & E
)
{
  Eigen::RowVector3d fp;
  face_points.resize(F.rows, 3);
  int i;
  for (i = 0; i < F.rows(); i++) {
    fp = (V.row(F(i, 0)) + V.row(F(i, 1)) + V.row(F(i, 2)) + V.row(F(i, 3))) / 4.0;
    face_points.row(i) = fp;
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
  std::vector<std::pair> E;
  std::vector<Eigen::RowVector3d> mid_points;
  std::unordered_map<int, std::vector<int>> ef_map;
  std::unordered_map<int, std::vector<int>> fe_map;
  // get edges, mid points, edge face map and face edge map.
  get_edges_and_related(V, F, E, mid_points, ef_map, fe_map);

  // get vertix edge map and vertice face map
  std::unordered_map<int, std::vector<int>> ve_map;
  std::unordered_map<int, std::vector<int>> vf_map;
  get_vertex_edge_map(V, E, ve_map);
  get_vertex_face_map(V, F, vf_map);

  // get edge points
  std::vector<Eigen::RowVector3d> edge_points;
  get_edge_points(mid_points, face_points, ef_map, edge_points);

  // step 3, for each vertex point, its coordinates are updated from(new_coords) :
  //  the old coordinates(old_coords),
  //  the average of the face points of the faces the point belongs to(avg_face_points),
  //  the average of the centers of edges the point belongs to(avg_mid_edges),
  //  how many faces a point belongs to(n), then use txhis formula :
  Eigen::MatrixXd vertex_points;
  get_vertex_points(V, ve_map, vf_map, face_points, mid_points, vertex_points);

  // last step, for the new vertices and faces
  new_V.resize(V.rows()+E.rows()+F.rows(), 3);
  new_F.resize(F.rows() * 4, 4);
  int i;
  for (i = 0; i < F.rows(); i++) {
    
  }

  // if not the last iteration, go to the next iteration
  catmull_clark(new_V, new_F, (num_iters - 1), SV, SF);
  ////////////////////////////////////////////////////////////////////////////
}
