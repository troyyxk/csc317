#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////

  ////Hint:
  V.resize(8,3);
  F.resize(6,4);
  UV.resize(14,2);
  UF.resize(6,4);
  NV.resize(6,3);
  NF.resize(6,4);

  // https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html

  // 3D vertex positions V and faces F,
  // 2D parametrization positions UV and faces UF,
  // 3D normal vectors NV and faces NF to a .obj file.

  // V << 0,0,0, // 0
  //     0, 0, 1, // 1
  //     0, 1, 0, // 2
  //     0, 1, 1, // 3
  //     1, 0, 0, // 4
  //     1, 0, 1, // 5
  //     1, 1, 0, // 6
  //     1, 1, 1; // 7

  // F << 0, 4, 5, 1,
  //     2, 0, 4, 6, 
  //     6, 4, 5, 7,
  //     5, 7, 3, 6,
  //     2, 0, 1, 3,
  //     6, 7, 3, 2;

  V << 0,0,0, // 0
      0, 0, -1, // 1
      0, 1, 0, // 2
      0, 1, -1, // 3
      1, 0, 0, // 4
      1, 0, -1, // 5
      1, 1, 0, // 6
      1, 1, 1; // 7

  F << 0, 4, 6, 2, // green  
      0, 1, 3, 2, // red
      0, 4, 5, 1, // white
      2, 6, 7, 3, // yellow
      6, 4, 5, 7, // blue
      5, 7, 3, 6; // orage

  UV << 0.25, 0, // 0
        0.5, 0, // 1
        0, 0.25, //2
        0.25, 0.25, //3
        0.5, 0.25, // 4
        0.75, 0.25, // 5
        1, 0.25, // 6
        0, 0.5, // 7
        0.25, 0.5, // 8
        0.5, 0.5, // 9
        0.75, 0.5, // 10
        1, 0.5, // 11
        0.25, 0.75, // 12
        0.5, 0.75; // 13

  UF << 3, 4, 9, 8, // green
        2, 3, 8, 7, // red
        0, 1, 4, 3, // white
        8, 9, 13, 12, // yellow
        4, 5, 10, 9, // blue
        5, 6, 11, 10; // orage

  NV << 0, 0, 1, // green
        -1, 0, 0, // red
        0, -1, 0, // white
        0, 1, 0, // yellow
        1, 0, 0, // blue
        0, 0, -1; // orage

  NF << 0, 0, 0,
        1, 1, 1,
        2, 2, 2,
        3, 3, 3,
        4, 4, 4,
        5, 5, 5;

}
