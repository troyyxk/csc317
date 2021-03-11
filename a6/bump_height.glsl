// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  float noise = improved_perlin_noise((s + vec3(0.1, 0.1, 0.1))*3);
  if(is_moon)
  { 
    noise = smooth_heaviside(noise,1) * 0.1;
  }
  else 
  {
    noise = smooth_heaviside(noise,20) * 0.1;
  }

  if (noise <-0.1){
    noise = -0.1;
  }
  if(noise> 0.1){
    noise = 0.1;
  }
  return noise;
  /////////////////////////////////////////////////////////////////////////////
}
