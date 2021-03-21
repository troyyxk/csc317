#include "signed_incidence_matrix_dense.h"

void signed_incidence_matrix_dense(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::MatrixXd & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  A = Eigen::MatrixXd::Zero(E.rows(),n);
  int i, j, e, k;
  int edge_amount = E.rows();
  for (e=0; e<edge_amount; e++){
    i = E(e, 0);
    j = E(e, 1);
    for (k=0; k<n; k++){
      if (k == i) {
        A(e, k) = 1.0;
      }
      if (k == e) {
        A(e, k) = -1.0;
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////
}
