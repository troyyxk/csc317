#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tips = transformed_tips(copy, b);
    return (tips - xb0).squaredNorm();
  };
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tips = transformed_tips(copy, b);
    Eigen::MatrixXd J;

    
    return Eigen::VectorXd::Zero(A.size());
  };
  proj_z = [&](Eigen::VectorXd & A)
  {
    int i;
    int s_size = skeleton.size();
    for (i=0; i<s_size; i++){
      A[i*3] = std::maxc(skeleton[i].xzx_min[0], std::min(skeleton[i].xzx_max[0], A[i*3]));
      A[(i*3)+1] = std::max(skeleton[i].xzx_min[1], std::min(skeleton[i].xzx_max[1], A[(i*3)+1]));
      A[(i*3)+2] = std::max(skeleton[i].xzx_min[2], std::min(skeleton[i].xzx_max[2], A[(i*3)+2]));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}
