#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
	const Eigen::MatrixXd & V,
	const Eigen::MatrixXi & F,
	const double corner_threshold,
	Eigen::MatrixXd & N)
{
	N = Eigen::MatrixXd::Zero(F.rows()*3,3);

	std::vector< std::vector<int> > VF;
	vertex_triangle_adjacency(F, V.rows(), VF);

	Eigen::Vector3d a, b, c;
	for (int i = 0; i < F.rows(); i++) {
		a = V.row(F(i, 0)); b = V.row(F(i, 1)); c = V.row(F(i, 2));
		Eigen::Vector3d face_normal = triangle_area_normal(a, b, c).normalized();

		for (int j = 0; j < 3; j++) {
			Eigen::Vector3d corner_normal(0.0, 0.0, 0.0);
			std::vector<int> adj_faces = VF[F(i, j)];
			
			Eigen::RowVector3d adj_normal;
			for (int idx : adj_faces) {
				a = V.row(F(idx, 0)); b = V.row(F(idx, 1)); c = V.row(F(idx, 2));
				adj_normal = triangle_area_normal(a, b, c).normalized();
				if (face_normal.dot(adj_normal) > cos(3.1415926 * corner_threshold / 180)) {
					corner_normal += adj_normal;
				}
			}

			N.row(3 * i + j) = corner_normal.normalized();
		}
	}
}

