#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::VectorXd og_a = transformed_tips(skeleton, b);
  Eigen::VectorXd a;
  double extra = 0.000000001;
  int num_skeleton = skeleton.size();
  int i, j;
  for (i=0; i<num_skeleton; i++) {
    for (j=0; j<3; j++) {
      Skeleton cur = skeleton;
      cur[i].xzx(j) += extra;
      a = transformed_tips(cur, b);
      J.col(i * 3 + j) = (a - og_a) / extra;
    }
  }
  /////////////////////////////////////////////////////////////////////////////
}
