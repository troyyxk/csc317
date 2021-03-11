// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step

float interpolate(float a0, float a1, float w) {
  return (a1 - a0) * w + a0;
}

float perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // https://en.wikipedia.org/wiki/Perlin_noise
  int i;
  float x = st.x;
  float y = st.y;
  float z = st.z;
  int x0 = int(floor(x));
  int x1 = x0 + 1;
  int y0 = int(floor(y));
  int y1 = y0 + 1;
  int z0 = int(floor(z));
  int z1 = z0 + 1;

  vec3 corners[8];
  corners[0] = vec3(x0, y0, z0);
  corners[1] = vec3(x1, y0, z0);
  corners[2] = vec3(x0, y1, z0);
  corners[3] = vec3(x1, y1, z0);
  corners[4] = vec3(x0, y0, z1);
  corners[5] = vec3(x1, y0, z1);
  corners[6] = vec3(x0, y1, z1);
  corners[7] = vec3(x1, y1, z1);

  vec3 g[8];
  for (i=0; i<8; i++){
    g[i] = random_direction(corners[i]);
  }

  vec3 d[8];
  for (i=0; i<8; i++){
    d[i] = st-corners[i];
  }

  float n[8];
  for (i=0; i<8; i++){
    n[i] = dot(g[i], d[i]);
  }

  float sstep_x = smooth_step(st.x-x0);
  float sstep_y = smooth_step(st.y-y0);
  float sstep_z = smooth_step(st.z-z0);

  float ix1 = interpolate(n[0], n[1], sstep_x);
  float ix2 = interpolate(n[2], n[3], sstep_x);
  float ix3 = interpolate(n[4], n[5], sstep_x);
  float ix4 = interpolate(n[6], n[7], sstep_x); 
  float ix5 = interpolate(ix1, ix2, sstep_y);
  float ix6 = interpolate(ix3, ix4, sstep_y);
  float ix7 = interpolate(ix5, ix6, sstep_z);

  return ix7;
  /////////////////////////////////////////////////////////////////////////////
}

