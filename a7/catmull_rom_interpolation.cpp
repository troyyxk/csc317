#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // https://en.wikipedia.org/wiki/Cubic_Hermite_spline
  return Eigen::Vector3d(0,0,0);
  /////////////////////////////////////////////////////////////////////////////
}
