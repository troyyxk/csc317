#include "signed_incidence_matrix_sparse.h"
#include <vector>

void signed_incidence_matrix_sparse(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::SparseMatrix<double>  & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Triplet<double> > ijv;
  // ijv.emplace_back(0,0,1234.5678);
  // A.resize(E.rows(),n);
  // A.setFromTriplets(ijv.begin(),ijv.end());

  int e_size = E.rows();
  int i, j, e, k;
  for (e=0; e<e_size; e++){
    i = E(e, 0);
    j = E(e, 1);
    for (k=0; k<n; k++){
      if (k == i) {
        ijv.emplace_back(e, k, 1.0);
      }
      if (k == j) {
        ijv.emplace_back(e, k, -1.0);
      }
    }
  }
  A.resize(E.rows(),n);
  A.setFromTriplets(ijv.begin(),ijv.end());
  //////////////////////////////////////////////////////////////////////////////
}
