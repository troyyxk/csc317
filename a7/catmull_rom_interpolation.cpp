#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // https://en.wikipedia.org/wiki/Cubic_Hermite_spline
  double time_0 = keyframes[0].first;
  double time_1 = keyframes[1].first;
  // t is t'
  double new_t = fmod(t, keyframes.back().first);
  double cur_t = (new_t - time_0)/(time_1 - time_0);

  int ind=0;
  while (keyframes[ind].first < new_t) {
    ind++;
  }

  int ind1, ind2;
  ind1 = ind1 + 1;
  ind2 = ind2 + 2;
  if (ind1 >= keyframes.size()) {
    ind1 = ind;
  }
  if (ind2 >= keyframes.size()) {
    ind2 = ind;
  }

  double t0, t1, t2;
  Eigen::Vector3d theta0, theta1, theta2, m0, m1;
  t0 = keyframes[ind].first;
  t1 = keyframes[ind1].first;
  t2 = keyframes[ind2].first;
  theta0 = keyframes[ind].second;
  theta1 = keyframes[ind1].second;
  theta2 = keyframes[ind2].second;
  m0 = (theta1 -theta0)/(t1 - t0);
  m1 = (theta2 -theta1)/(t2 - t1);


  return (2*pow(t, 3) - 3*pow(t, 2) + 1) * theta0 + \
          (pow(t, 3) - 2*pow(t, 2) + t) * m0 + \
          ((-2)*pow(t, 3) + 3*pow(t, 3)) * theta1 + \
          (pow(t, 3) - pow(t, 2)) * m1;
  /////////////////////////////////////////////////////////////////////////////
}
