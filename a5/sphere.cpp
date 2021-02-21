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

  V.resize((num_faces_u + 1) * (num_faces_v + 1),3);
  F.resize(num_faces_u * num_faces_v,4);
  UV.resize((num_faces_u + 1) * (num_faces_v + 1),2);
  UF.resize(num_faces_u * num_faces_v,4);
  NV.resize((num_faces_u + 1) * (num_faces_v + 1),3);
  NF.resize(num_faces_u * num_faces_v,4);

  const double pi = 3.14159265358979323846;
  double x, y, z, r, u, v, t, ft, p, fp;
  int c1, c2, c3, c4;
  int i, j, vind, find;
  r = 1.0;
  ft = pi/num_faces_v;
  fp = (2*pi)/num_faces_u;

  vind = 0;
  find = 0;
  for (i=0; i<(num_faces_u + 1); i++){
    for (j=0; j<(num_faces_v + 1); j++){
      x = -r*sin(ft *j)*cos(fp*i);
      y = -r*sin(ft *j)*sin(fp*i);
      z = -r*cos(ft *j);

      V.row(vind) = Eigen::RowVector3d(x, y, z);
      UV(vind, 0) = ((double)i)/num_faces_u;
      UV(vind, 1) = ((double)j)/num_faces_v;
      NV.row(vind) = Eigen::RowVector3d(x, y, z);

      if ((i<num_faces_u) && (j<num_faces_v)){
        c1 = i * (num_faces_v+1) + j;
        c2 = c1 +1;
        c4 = (i+1) * (num_faces_v+1) + j;
        c3 = c4 + 1;
        F.row(find) = Eigen::RowVector4i(c1, c2, c3, c4);
        UF.row(find) = Eigen::RowVector4i(c1, c2, c3, c4);
        NF.row(find) = Eigen::RowVector4i(c1, c2, c3, c4);
        find++;
      }
      vind++;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
