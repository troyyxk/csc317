#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////
  // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
  // https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html

  std::ofstream file;
  file.open(filename);
  if (!file.is_open()) {
    return false;
  }

  int i;

  // v is a vertex
  // v 1.000000 -1.000000 -1.000000
  for (i=0; i<V.rows(); i++) {
    file << "V" << " " << V(i, 0) << " " << V(i, 1) << " " << V(i, 2) << "\n";
  }

  // vt is the texture coordinate of one vertex
  // vt 0.748573 0.750412
  // 2D parametrization positions UV
  for (i=0; i<UV.rows(); i++) {
    file << "vt" << " " << UV(i, 0) << " " << UV(i, 1) << "\n";
  }

  // vn is the normal of one vertex
  // vn 0.000000 0.000000 -1.000000
  // 3D normal vectors NV
  for (i=0; i<NV.rows(); i++) {
    file << "vn" << " " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << "\n";
  }

  // f is a face
  // f 5/1/1 1/2/1 4/3/1
  // vertex ind/texture coordinate/normal ind
  for (i=0; i<F.rows(); i++) {
    file << "f";
    file << " " << F(i, 0)+1 << "/" << UF(i, 0)+1 << "/" << NF(i,0)+1;
    file << " " << F(i, 1)+1 << "/" << UF(i, 1)+1 << "/" << NF(i,1)+1;
    file << " " << F(i, 2)+1 << "/" << UF(i, 2)+1 << "/" << NF(i,2)+1;
    file << "\n";
  }

  return true;
}