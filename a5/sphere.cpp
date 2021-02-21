#include "sphere.h"
#include <iostream>
// #include <math.h>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // https://en.wikipedia.org/wiki/Spherical_coordinate_system
  int total_face_num = num_faces_u * num_faces_v;
  int total_vertex_num = (num_faces_u + 1) * (num_faces_v + 1);

  V.resize(total_vertex_num,3);
  F.resize(total_face_num,4);
  UV.resize(total_vertex_num,2);
  UF.resize(total_face_num,4);
  NV.resize(total_vertex_num,3);
  NF.resize(total_face_num,4);

  const double pi = 3.14159265358979323846;
  double x, y, z, r, u, v, t, ft, p, fp;
  int i, j, ind;
  r = 1.0;
  ft = pi/num_faces_v;
  fp = (2*pi)/num_faces_u;

  ind = 0;
  for (i=0; i<(num_faces_u + 1); i++){
    for (j=0; j<(num_faces_v + 1); j++){
      x = -r*sin(ft *j)*cos(fp*i);
      y = -r*sin(ft *j)*sin(fp*i);
      z = -r*cos(ft *j);

      V.row(ind) = Eigen::RowVector3d(x, y, z);
      UV(ind, 0) = ((double)i)/num_faces_u;
      UV(ind, 1) = ((double)j)/num_faces_v;
      NV.row(ind) = Eigen::RowVector3d(x, y, z);
      ind++;
    }
  }

  int c1, c2, c3, c4;
  ind = 0;
  for (i=0; i<num_faces_u; i++){
    for (j=0; j<num_faces_v; j++){
      c1 = i * (num_faces_v+1) + j;
      c2 = c1 +1;
      c4 = (i+1) * (num_faces_v+1) + j;
      c3 = c4 + 1;
      F.row(ind) = Eigen::RowVector4i(c1, c2, c3, c4);
      UF.row(ind) = Eigen::RowVector4i(c1, c2, c3, c4);
      NF.row(ind) = Eigen::RowVector4i(c1, c2, c3, c4);
      ind++;
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
