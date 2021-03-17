#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  int num_rest = V.rows();
  int num_skeleton = skeleton.size();
  U.resize(num_rest, 3);
  int i, j;
  Eigen::Vector4d cur;


  for (i=0; i<num_rest; i++) {
    cur = Eigen::Vector4d(0, 0, 0, 0);
    for (j=0; j<num_skeleton; j++) {
      Eigen::Vector4d vi = Eigen::Vector4d(1, 1, 1, 1);
      if (skeleton[j].weight_index != -1) {
        vi(0) = V(i, 0);
        vi(1) = V(i, 1);
        vi(2) = V(i, 2);
        cur += W(i, skeleton[j].weight_index) * T[j] * vi;
      }
    }
    U(i, 0) = base(0);
    U(i, 1) = base(1);
    U(i, 2) = base(2);
  }
  
  return;
  /////////////////////////////////////////////////////////////////////////////
}
