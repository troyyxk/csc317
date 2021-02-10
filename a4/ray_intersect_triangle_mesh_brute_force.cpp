#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <cassert>
#include <fstream>
#include <iostream>

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // https://stackoverflow.com/questions/51640997/how-to-get-the-number-of-rows-and-columns-of-an-eigenmatrixxd
  hit_t = 0;
  hit_f = 0;
  bool isHit = false;
  bool isFirst = true;
  double cur_t;
  int i, j;
  Eigen::RowVector3d A;
  Eigen::RowVector3d B;
  Eigen::RowVector3d C;
  // assert((F.cols() == 3) && "Triangle has 3 corners.");
  for (i=0; i<F.rows(); i++){
    A = V.row(F(i, 0));
    B = V.row(F(i, 1));
    C = V.row(F(i, 2));
    if (ray_intersect_triangle(ray, A, B, C, min_t, max_t, cur_t)){
      isHit = true;
      // first or smaller
      if (isFirst || hit_t > cur_t){
        isFirst = false;
        hit_t = cur_t;
        hit_f = i;
      }
    }
  }
  return isHit;
  ////////////////////////////////////////////////////////////////////////////
}
