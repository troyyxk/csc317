#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>
#include <stdio.h>      /* printf */
#include <math.h>       /* pow */

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  int e_size = E.rows();
  int v_size = V.rows();
  int i, j;
  r.resize(e_size);
  for (i=0; i<e_size; i++) {
    r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
  }
  M = Eigen::MatrixXd::Zero(v_size, v_size);
  for (i=0; i<v_size; i++) {
    M(i, i) = m(i);
  }
  A = Eigen::MatrixXd::Zero(e_size, v_size);
  signed_incidence_matrix_dense(v_size, E, A);
  int b_size = b.rows();
  C = Eigen::MatrixXd::Zero(b_size, v_size);
  for (i=0; i<b_size; i++) {
    for (j=0; j<v_size; j++) {
      if(j == b(i)) {
        C(i, j) = 1;
      }
    }
  }
  Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(V.rows(),V.rows());
  double w=1e10;
  Q = k*(A.transpose())*A + (1/pow(delta_t, 2))*M + w*C.transpose()*C;
  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
