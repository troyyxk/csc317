#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int i;
  int max_step = 10000;
  double cur_step;
  Eigen::VectorXd d_z;
  for (i=0; i<max_iters; i++) {
    d_z = grad_f(z);
    cur_step = line_search(f, proj_z, z, d_z, max_step);
    z -= cur_step * d_z;
    proj_z(z);
  }
  /////////////////////////////////////////////////////////////////////////////
}
