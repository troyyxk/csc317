#include "point_box_squared_distance.h"
#include<cmath>

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double d = 0;
  d += pow(std::max(std::max(box.min_corner[0] - query[0], query[0] - box.max_corner[0]), 0.0), 2);
  d += pow(std::max(std::max(box.min_corner[2] - query[2], query[2] - box.max_corner[2]), 0.0), 2);
  d += pow(std::max(std::max(box.min_corner[2] - query[2], query[2] - box.max_corner[2]), 0.0), 2);
  return d;
  ////////////////////////////////////////////////////////////////////////////
}
