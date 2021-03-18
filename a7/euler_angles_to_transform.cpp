#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html#:~:text=The%204%20by%204%20transformation,in%20the%20first%20three%20columns.
  Eigen::Affine3d x0, z0, x1;
  double a, b, c;

  double pi = 3.14159265358979323846;
  Eigen::Vector3d new_xzx = xzx * pi /180.0;
  a = new_xzx(0);
  b = new_xzx(1);
  c = new_xzx(2);

  x0.matrix() << 
    1,0,0,0,
    0,cos(a),-sin(a),0,
    0,sin(a),cos(a),0,
    0,0,0,1;

  z0.matrix() << 
    cos(b),-sin(b),0,0,
    sin(b),cos(b),0,0,
    0,0,1,0,
    0,0,0,1;

  x1.matrix() << 
    1,0,0,0,
    0,cos(c),-sin(c),0,
    0,sin(c),cos(c),0,
    0,0,0,1;
  
  return x0 * z0 *x1;
  /////////////////////////////////////////////////////////////////////////////
}
