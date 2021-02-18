#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:

  int i, j;
  for (i=0; i<num_vertices; i++) {
    for (j=0; j<F.rows(); j++){
      if((i == F(j, 0)) || (i == F(j, 1)) || (i == F(j, 2))) {
        VF(i).push_back(j);
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}

