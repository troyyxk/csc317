#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  int num_vertices = V.rows();
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, num_vertices, VF):

  int i, j,  ia, ib, ic;
  Eigen::RowVector3d a, b, c;

  Eigen::RowVector3d
  for (i=0; i<VF.rows(); i++) {
    for (j : VF.row(i)) {
      ia = F(j, 0);
      ib = F(j, 1);
      ic = F(j, 2);
      a = V.row(ia);
      b = V.row(ib);
      c = V.row(ic);
      N.row(i) += triangle_area_normal(a, b, c);
    }
    N.row(i) = N.row(i).normalized();
  }




  ////////////////////////////////////////////////////////////////////////////
}
