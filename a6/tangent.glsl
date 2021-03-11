// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  T = cross(N, vec3(0,1,0));
  if(length(T) < length(cross(N, vec3(0,0,1)))){
    T = cross(N, vec3(0,0,1));
  }
  B = normalize(cross(N, T));
  T = normalize(T);
  /////////////////////////////////////////////////////////////////////////////
}
