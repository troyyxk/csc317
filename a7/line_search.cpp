#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  int max_iteration = 100;
  int i = 0;
  double cur_step = max_step;
  Eigen::VectorXd v = z;
  while(f(v) >= f(z)) {
    v = z - cur_step*dz;
    proj_z(v);
    cur_step = cur_step * (1/2);
    i++;
    if(i >= max_iteration) {
      return cur_step;
    }
  }
  return cur_step;
  /////////////////////////////////////////////////////////////////////////////
}
