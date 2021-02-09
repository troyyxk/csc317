#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool hit = false;
  Eigen::Vector3d A = std::get<0>(corners);
  Eigen::Vector3d B = std::get<1>(corners);
  Eigen::Vector3d C = std::get<2>(corners);
  Eigen::Vector3d t1 = A - B;
  Eigen::Vector3d t2 = A - C;

  double a = t1[0];
  double b = t1[1];
  double c = t1[2];
  double d = t2[0];
  double e = t2[1];
  double f = t2[2];
  double g = ray.direction[0];
  double h = ray.direction[1];
  double i = ray.direction[2];

  double j = A[0] - ray.origin[0];
  double k = A[1] - ray.origin[1];
  double l = A[2] - ray.origin[2];

  double m = a*(e*i-h*f) + b*(g*f-d*i) +c*(d*h-e*g);
  double cur_t = -(f*(a*k-j*b) + e*(j*c-a*l) + d*(b*l-k*c))/m;
  if (cur_t < min_t){
    return false;
  }
  double gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/m;
  if ((gamma < 0) || (gamma > 1)){
    return false;
  }
  double beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/m;
  if ((beta < 0) || (beta > 1-gamma)){
    return false;
  }
  
  hit = true;
  t = cur_t;

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}

