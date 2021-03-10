// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec3 ka = vec3(0.01,0.01,0.01);
  vec3 kd;
  if (is_moon) {
    kd = vec3(0.5,0.5,0.5);
  } else {
    kd = vec3(0,0,1);
  }
  vec3 ks = vec3(0.9, 0.9, 0.9);
  vec3 n = normalize(normal_fs_in);
  vec3 v = normalize(-view_pos_fs_in.xyz);
  float theta = (M_PI/2.0)*animation_seconds;
  mat4 ry = mat4(
      cos(theta),0,-sin(theta),0,
      0,1,0,0,
      sin(theta),0,cos(theta),0,
      0,0,0,1);
  vec3 l = normalize(ry * vec4(1.0, 1.0, 1.0, 1.0)).xyz;
  color = blinn_phong(ka, kd, ks, 1000, n, v, l);
  /////////////////////////////////////////////////////////////////////////////
}
