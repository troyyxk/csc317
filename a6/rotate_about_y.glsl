// Inputs:
//   theta  amount y which to rotate (in radians)
// Return a 4x4 matrix that rotates a given 3D point/vector about the y-axis by
// the given amount.
mat4 rotate_about_y(float theta)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // https://math.stackexchange.com/questions/134741/a-4x4-homogeneous-matrix-for-a-90-degree-rotation-about-y-axis
  return mat4(
  cos(theta),0,sin(theta),0,
  0,1,0,0,
  -sin(theta),0,cos(theta),0,
  0,0,0,1);
  /////////////////////////////////////////////////////////////////////////////
}

