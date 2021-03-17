#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  int i;
  for (i=0; i<skeleton.size(); i++){
    Bone bone = skeleton[i];
    if (bone.parent_index < 0){
      return Eigen::Affine3d::Identity();
    }
    Eigen::Affine3d Tpi = T[bone.parent_index];
    Eigen::Affine3d Ti = rest_T;
    Eigen::Affine3d Tii = Ti.inverse();
    Eigen::Affine3d R = euler_angles_to_transform(bone.xzx);

    return Tpi * Ti * R * Tii;


  }
  /////////////////////////////////////////////////////////////////////////////
}
