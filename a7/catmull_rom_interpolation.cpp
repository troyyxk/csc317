#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
  if (keyframes.empty()) {
    return Eigen::Vector3d(0, 0, 0);
  }
  double time_0 = keyframes[0].first;
  double time_1 = keyframes[1].first;
  // t is t'
  double new_t = fmod(t, keyframes.back().first);

  int ind=0;
  while (keyframes[ind].first < new_t) {
    if (ind >= (keyframes.size() - 1)) {
      break;
    }
    ind++;
  }

  int ind0, ind1, ind2, ind3;
  ind0 = ind - 2;
  ind1 = ind - 1;
  ind2 = ind;
  ind3 = ind + 1;
  if ((ind0 < 0) || ind1 < 0 || (ind3 >= keyframes.size())) {
    return Eigen::Vector3d(0, 0, 0);
  }

  // if (ind0 < 0) {
  //   ind0 = 0;
  // }
  // if (ind1 < 0) {
  //   ind1 = ind;
  // }
  // if (ind3 >= keyframes.size()) {
  //   ind3 = ind;
  // }

  double t0, t1, t2, t3;
  Eigen::Vector3d P0, P1, P2, P3;
  t0 = keyframes[ind0].first;
  t1 = keyframes[ind1].first;
  t2 = keyframes[ind2].first;
  t3 = keyframes[ind3].first;
  P0 = keyframes[ind0].second;
  P1 = keyframes[ind1].second;
  P2 = keyframes[ind2].second;
  P3 = keyframes[ind3].second;

  Eigen::Vector3d A1, A2, A3, B1, B2, C;
  A1 = ((t1 - new_t)/(t1 - t0))*P0 + ((new_t - t0)/(t1 - t0))*P1;
  A2 = ((t2 - new_t)/(t2 - t1))*P1 + ((new_t - t1)/(t2 - t1))*P2;
  A3 = ((t3 - new_t)/(t3 - t2))*P2 + ((new_t - t2)/(t3 - t2))*P3;

  B1 = ((t2 - new_t)/(t2 - t0))*A1 + ((new_t - t0)/(t2 - t0))*A2;
  B2 = ((t3 - new_t)/(t3 - t1))*A2 + ((new_t - t1)/(t3 - t1))*A3;

  C = ((t2 - new_t)/(t2 - t1))*B1 + ((new_t - t1)/(t2 - t1))*B2;
  return C;

  /////////////////////////////////////////////////////////////////////////////
}


// #include "catmull_rom_interpolation.h"
// #include <Eigen/Dense>

// Eigen::Vector3d catmull_rom_interpolation(
//   const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
//   double t)
// {
//   /////////////////////////////////////////////////////////////////////////////
//   // Replace with your code
//   // https://en.wikipedia.org/wiki/Cubic_Hermite_spline
//  if (keyframes.empty()) {
//    return Eigen::Vector3d(0, 0, 0);
//  }
//   double time_0 = keyframes[0].first;
//   double time_1 = keyframes[1].first;
//   // t is t'
//   double new_t = fmod(t, keyframes.back().first);
//   double cur_t = (new_t - time_0)/(time_1 - time_0);

//   int ind=0;
//   while (keyframes[ind].first < new_t) {
//     ind++;
//   }

//   int ind1, ind2;
//   ind1 = ind1 + 1;
//   ind2 = ind2 + 2;
//   if (ind1 >= keyframes.size()) {
//     ind1 = ind;
//   }
//   if (ind2 >= keyframes.size()) {
//     ind2 = ind;
//   }

//   double t0, t1, t2;
//   Eigen::Vector3d theta0, theta1, theta2, m0, m1;
//   t0 = keyframes[ind].first;
//   t1 = keyframes[ind1].first;
//   t2 = keyframes[ind2].first;
//   theta0 = keyframes[ind].second;
//   theta1 = keyframes[ind1].second;
//   theta2 = keyframes[ind2].second;
//   m0 = (theta1 -theta0)/(t1 - t0);
//   m1 = (theta2 -theta1)/(t2 - t1);


//   return (2*pow(cur_t, 3) - 3*pow(cur_t, 2) + 1) * theta0 + \
//           (pow(cur_t, 3) - 2*pow(cur_t, 2) + cur_t) * m0 + \
//           ((-2)*pow(cur_t, 3) + 3*pow(cur_t, 3)) * theta1 + \
//           (pow(cur_t, 3) - pow(cur_t, 2)) * m1;
//   /////////////////////////////////////////////////////////////////////////////
// }