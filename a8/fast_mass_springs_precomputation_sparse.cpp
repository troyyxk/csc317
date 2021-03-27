#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // std::vector<Eigen::Triplet<double> > ijv;
  const int n = V.rows();
  // for(int i = 0;i<n;i++) ijv.emplace_back(i,i,1);

  int e_size = E.rows();
  int v_size = V.rows();
  int i, j;
  r.resize(e_size);
  for (i=0; i<e_size; i++) {
    r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
  }

  std::vector<Eigen::Triplet<double> > ijv;
  M.resize(v_size, v_size);
  for(i = 0;i<v_size;i++) ijv.emplace_back(i,i,m(i));
  M.setFromTriplets(ijv.begin(),ijv.end());

  A.resize(e_size, v_size);
  signed_incidence_matrix_sparse(v_size, E, A);

  int b_size = b.rows();
  std::vector<Eigen::Triplet<double> > ijv0;
  C.resize(b_size, v_size);
  for (i=0; i<b_size; i++) {
    for (j=0; j<v_size; j++) {
      if(j == b(i)) {
        ijv0.emplace_back(i,j,1);
      }
    }
  }
  C.setFromTriplets(ijv0.begin(),ijv0.end());

  Eigen::SparseMatrix<double> Q(n,n);
  double w=1e10;
  Q = k*(A.transpose())*A + (1/pow(delta_t, 2))*M + w*C.transpose()*C;
  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
