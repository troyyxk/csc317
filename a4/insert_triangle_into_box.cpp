#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double txmax = std::max(std::max(a[0], b[0]), c[0]);
  double txmin = std::min(std::min(a[0], b[0]), c[0]);
  double tymax = std::max(std::max(a[1], b[1]), c[1]);
  double tymin = std::min(std::min(a[1], b[1]), c[1]);
  double tzmax = std::max(std::max(a[2], b[2]), c[2]);
  double tzmin = std::min(std::min(a[2], b[2]), c[2]);

  B.min_corner[0] = std::min(txmin, B.min_corner[0]);
  B.max_corner[0] = std::max(txmax, B.max_corner[0]);
  B.min_corner[1] = std::min(tymin, B.min_corner[1]);
  B.max_corner[1] = std::max(tymax, B.max_corner[1]);
  B.min_corner[2] = std::min(tzmin, B.min_corner[2]);
  B.max_corner[2] = std::max(tzmax, B.max_corner[2]);
  ////////////////////////////////////////////////////////////////////////////
}


