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
  int i, j, vind, find;
  int c0, c1, c2, c3;
  r = 1.0;
  ft = pi/num_faces_v;
  fp = (2*pi)/num_faces_u;

  vind = 0;
  find = 0;
  for (i=0; i<(num_faces_u + 1); i++){
    for (j=0; j<(num_faces_v + 1); j++){
      x = -r*sin(ft *((double)j))*cos(fp*((double)i));
      y = -r*sin(ft *((double)j))*sin(fp*((double)i));
      z = -r*cos(ft *((double)j));

      V.row(vind) = Eigen::RowVector3d(x, y, z);
      UV(vind, 0) = ((double)i)/num_faces_u;
      UV(vind, 1) = ((double)j)/num_faces_v;
      NV.row(vind) = Eigen::RowVector3d(x, y, z);

      if ((i<num_faces_u) && (j<num_faces_v)){
        c0 = i * (num_faces_v+1) + j;
        c1 = c0 +1;
        c3 = (i+1) * (num_faces_v+1) + j;
        c2 = c3 + 1;
        F(find, 0) = c0;
        F(find, 1) = c1;
        F(find, 2) = c2;
        F(find, 3) = c3;

        UF(find, 0) = c0;
        UF(find, 1) = c1;
        UF(find, 2) = c2;
        UF(find, 3) = c3;

        NF(find, 0) = c0;
        NF(find, 1) = c1;
        NF(find, 2) = c2;
        NF(find, 3) = c3;
        find++;
      }
      vind++;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
