#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::VectorXd tip, tips;
  int b_size = b.size();
  tips.resize(3*b_size);
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> >  T;
  forward_kinematics(skeleton, T);

  int i, cur;
  for (i=0; i<b_size; i++) {
    cur = b[i];
    tip = T[cur] * skeleton[cur].rest_T * Eigen::Vector4d(skeleton[cur].length, 0, 0, 1);
    tips[i*3] = tip[0];
    tips[i*3 + 1] = tip[1];
    tips[i*3 + 2] = tip[2];

  }
  return tips;
  /////////////////////////////////////////////////////////////////////////////
}
