#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // d ray direction, e ray origin
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  double xd = d[0];
  double yd = d[1];
  double zd = d[2];
  double xe = e[0];
  double ye = e[1];
  double ze = e[2];
  double xmin = box.min_corner[0];
  double ymin = box.min_corner[1];
  double zmin = box.min_corner[2];
  double xmax = box.max_corner[0];
  double ymax = box.max_corner[1];
  double zmax = box.max_corner[2];
  double txmin, txmax, tymin, tymax, tzmin, tzmax;
  // formula on book p 317
  double ax = 1/xd;
  double ay = 1/yd;
  double az = 1/zd;

  if(ax >= 0){
    txmin = ax*(xmin-xe);
    txmax = ax*(xmax-xe);
  }else{
    txmin = ax*(xmax-xe);
    txmax = ax*(xmin-xe);
  }
  if(ay >= 0){
    tymin = ay*(ymin-ye);
    tymax = ay*(ymax-ye);
  }else{
    tymin = ay*(ymax-ye);
    tymax = ay*(ymin-ye);
  }
  if(az >= 0){
    tzmin = az*(zmin-ze);
    tzmax = az*(zmax-ze);
  }else{
    tzmin = az*(zmax-ze);
    tzmax = az*(zmin-ze);
  }

  // slides 19
  if(std::max(std::max(txmin, tymin), std::max(tzmin, min_t)) > std::min(std::min(txmax, tymax), std::min(tzmax, max_t))){
    return false;
  }

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
