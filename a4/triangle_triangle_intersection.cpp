#include "ray_intersect_triangle.h"
#include "triangle_triangle_intersection.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Ray ra1 = Ray(A0, A0-A1);
  Ray ra2 = Ray(A0, A0-A2);
  Ray ra3 = Ray(A1, A1-A2);
  Ray rb1 = Ray(B0, B0-B1);
  Ray rb2 = Ray(B0, B0-B2);
  Ray rb3 = Ray(B1, B1-B2);

  bool has_intersect = true;
  double t;
  has_intersect = has_intersect && ray_intersect_triangle(ra1, B0, B1, B2, 0, 1, t);
  has_intersect = has_intersect && ray_intersect_triangle(ra2, B0, B1, B2, 0, 1, t);
  has_intersect = has_intersect && ray_intersect_triangle(ra3, B0, B1, B2, 0, 1, t);
  has_intersect = has_intersect && ray_intersect_triangle(rb1, A0, A1, A2, 0, 1, t);
  has_intersect = has_intersect && ray_intersect_triangle(rb2, A0, A1, A2, 0, 1, t);
  has_intersect = has_intersect && ray_intersect_triangle(rb3, A0, A1, A2, 0, 1, t);
  return has_intersect; 
  ////////////////////////////////////////////////////////////////////////////
}
