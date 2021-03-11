// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

  // allien planet

  vec3 ka = vec3(0.01,0.01,0.01);
  vec3 ks = vec3(0.9, 0.9, 0.9);

  vec3 T, B;
  tangent(normal_fs_in, T, B);
  float e = 0.000001;
  vec3 p = bump_position(is_moon, sphere_fs_in);
  vec3 tp = bump_position(is_moon, (sphere_fs_in + (e*T)));
  vec3 bp = bump_position(is_moon, (sphere_fs_in + (e*B)));
  vec3 n = normalize(cross((tp-p)/e, (bp-p)/e));

  vec3 v = normalize(-view_pos_fs_in.xyz);
  float theta = (M_PI/2.0)*animation_seconds;
  mat4 ry = mat4(
      cos(theta),0,-sin(theta),0,
      0,1,0,0,
      sin(theta),0,cos(theta),0,
      0,0,0,1);
  vec3 l = normalize(ry * vec4(1.0, 1.0, 1.0, 1.0)).xyz;

  vec3 kd;
  if (is_moon) {
    if (bump_height(is_moon, sphere_fs_in)>0){
      kd = vec3(1,0,0);
    }else{
      kd = vec3(0,1,1);
    }
  } else {
    if (bump_height(is_moon, sphere_fs_in)>0){
      kd = vec3(1,0,0);
    }else{
      kd = vec3(0,1,1);
    }
  }

  color = blinn_phong(ka, kd, ks, 1000, n, v, l);
  /////////////////////////////////////////////////////////////////////////////
}
