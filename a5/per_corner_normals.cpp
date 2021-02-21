#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  const double pi = 3.14159265358979323846;
  double epsilon = cos((pi*corner_threshold)/180);
  int num_vertices = V.rows();
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, num_vertices, VF);
  Eigen::RowVector3d nf, ng, cur_result;
  cur_result = Eigen::RowVector3d(0, 0, 0);

  int i, k;
  for (i=0; i<F.rows(); i++) {
    nf = triangle_area_normal(V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)));
    for (k=0; k<F.cols(); k++) {
      for (int j : VF[F(i, k)]) {
        ng = triangle_area_normal(V.row(F(j, 0)), V.row(F(j, 1)), V.row(F(j, 2)));
        if (nf.dot(ng) > epsilon) {
          cur_result += ng;
        }
      }
      cur_result = cur_result.normalized();
  		N.row(i*3+k) = cur_result;
      cur_result = Eigen::RowVector3d(0, 0, 0);
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////
}
