#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

Eigen::Affine3d recursion(
  const Skeleton& skeleton,
  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> >& T,
  int cur)
{
  Bone bone = skeleton[cur];
  Eigen::Affine3d Tpi, Ti, Tii, R;
  if (bone.parent_index < 0){
    Tpi = Eigen::Affine3d::Identity();
    return Tpi;
  }
  else if (skeleton[bone.parent_index].parent_index < 0){
    Tpi = T[bone.parent_index];
  }
  else {
    Tpi = recursion(skeleton, T, bone.parent_index);
  }
  Ti = bone.rest_T;
  Tii = Ti.inverse();
  R = euler_angles_to_transform(bone.xzx);

  return Tpi * Ti * R * Tii;
}

void forward_kinematics(
  const Skeleton& skeleton,
  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> >& T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(), Eigen::Affine3d::Identity());
  Eigen::Affine3d Tpi, Ti, Tii, R;
  int i;
  for (i = 0; i < skeleton.size(); i++) {
    Bone bone = skeleton[i];
    if (bone.parent_index < 0) {
      T[i] = Eigen::Affine3d::Identity();
    }
    else {
      T[i] = recursion(skeleton, T, i);
    }


  }
  /////////////////////////////////////////////////////////////////////////////
}