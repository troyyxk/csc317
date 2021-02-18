#include "per_face_normals.h"
#include "triangle_area_normal.h"

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  N = Eigen::MatrixXd::Zero(F.rows(),3);
  int i, ia, ib, ic;
  Eigen::RowVector3d a, b, c, n;
  for (i=0; i<F.rows(); i++) {
    ia = F(i, 0);
    ib = F(i, 1);
    ic = F(i, 2);
    a = V.row(ia);
    b = V.row(ib);
    c = V.row(ic);

    n = triangle_area_normal(a, b, c);

    N(i, 0) = n(0);
    N(i, 1) = n(1);
    N(i, 2) = n(2);

  }

  ////////////////////////////////////////////////////////////////////////////
}
