// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec2 random_vector = (M_PI/2.0)*random2(seed);
  float a = random_vector.x;
  float b = random_vector.y;
  return normalize(vec3(cos(a)*sin(b),sin(a)*sin(b),cos(b)));
  /////////////////////////////////////////////////////////////////////////////
}
