#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();
// #include <math.h>       /* pow */
#include<cmath>

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  I = -1;
  sqrD = 0;
  int i;
  Eigen::RowVector3d d;
  bool first = true;
  int num_points = points.rows();
  double cur_sqrd;
  for (i=0; i<num_points; i++){
    d = points.row(i)-query;
    cur_sqrd = sqrt(pow(d[0], 2)+pow(d[1], 2)+pow(d[2], 2));
    if (first || cur_sqrd<sqrD){
      first = false;
      sqrD = cur_sqrd;
      I = i;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
