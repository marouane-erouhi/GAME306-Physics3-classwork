#include "Box.h"
#include "QMath.h"

void GEOMETRY::Box::generateVerticesAndNormals() {
/*
	// Define the vertices of the cube in local space
	MATH::Vec3 localVertices[] = {
		MATH::Vec3(-1, -1, -1), // 0: Bottom-Left-Back
		MATH::Vec3(1, -1, -1),  // 1: Bottom-Right-Back
		MATH::Vec3(1, 1, -1),   // 2: Top-Right-Back
		MATH::Vec3(-1, 1, -1),  // 3: Top-Left-Back
		MATH::Vec3(-1, -1, 1),  // 4: Bottom-Left-Front -x -y +z
		MATH::Vec3(1, -1, 1),   // 5: Bottom-Right-Front
		MATH::Vec3(1, 1, 1),    // 6: Top-Right-Front
		MATH::Vec3(-1, 1, 1)    // 7: Top-Left-Front
	};
	// Define the normals of the cube in local space
	MATH::Vec3 localNormals[] = {
		MATH::Vec3(0, 0, -1),  // Back face normal		-z
		MATH::Vec3(0, 0, 1),   // Front face normal		+z
		MATH::Vec3(-1, 0, 0),  // Left face normal		-x
		MATH::Vec3(1, 0, 0),   // Right face normal		+x
		MATH::Vec3(0, -1, 0),  // Bottom face normal	-y
		MATH::Vec3(0, 1, 0)    // Top face normal		+y
	};
	int indices[] = {
		4, 5, 6, 6, 7, 4,  // Front		(vertices 4, 5, 6, 7 form the front face)
		0, 1, 2, 2, 3, 0,  // Back		(vertices 0, 1, 2, 3 form the back face)
		0, 1, 5, 5, 4, 0,  // Bottom	(vertices 0, 1, 5, 4 form the bottom face)
		2, 3, 7, 7, 6, 2,  // Top		(vertices 2, 3, 7, 6 form the top face)
		0, 3, 7, 7, 4, 0,  // Left		(vertices 0, 3, 7, 4 form the left face)
		1, 2, 6, 6, 5, 1   // Right		(vertices 1, 2, 6, 5 form the right face)
	};
	std::vector<MATH::Vec3> tempVertecies;
	std::vector<MATH::Vec3> tempNormals;

	// Transform the vertices and normals by the center, halfExtents and orientation
	for (int i = 0; i < 8; i++) {
		//transform by center
		MATH::Vec3 vertex = MATH::Vec3(
			localVertices[i].x * halfExtents.x,
			localVertices[i].y * halfExtents.y,
			localVertices[i].z * halfExtents.z
		) + center;

		// rotate point
		vertex = MATH::QMath::rotate(vertex, orientation);
		MATH::Vec3 normal = MATH::QMath::rotate(localNormals[i % 6], orientation);
		MATH::VMath::normalize(normal);

		tempVertecies.push_back(vertex);
		tempNormals.push_back(normal);
	}
	// add in the correct order
	for (int i = 0; i < 36; i++) {
		vertices.push_back(tempVertecies[indices[i]]);
		normals.push_back(tempNormals[indices[i] / 6]);// face normal
	}
*/
	// Umer's code
	using namespace MATH;
// Set up the eight vertices of the box
// Umer will do three for now
	Vec3 topRightFront = center + Vec3(halfExtents.x, halfExtents.y, halfExtents.z);
	topRightFront = QMath::rotate(topRightFront, orientation);

	Vec3 topLeftFront = center + Vec3(-halfExtents.x, halfExtents.y, halfExtents.z);
	topLeftFront = QMath::rotate(topLeftFront, orientation);

	Vec3 bottomLeftFront = center + Vec3(-halfExtents.x, -halfExtents.y, halfExtents.z);
	bottomLeftFront = QMath::rotate(bottomLeftFront, orientation);

	// Let's make front face triangle 1 from the assignment doc
	// Ask Scott if the winding order matters here
	// Sam says anti-clockwise order so it wont backface cull
	// Umer is doing anti-clockwise, so fingers crossed it works
	vertices.push_back(topRightFront);
	vertices.push_back(topLeftFront);
	vertices.push_back(bottomLeftFront);
	// All normals point along z for this triangle
	normals.push_back(Vec3(0, 0, 1));
	normals.push_back(Vec3(0, 0, 1));
	normals.push_back(Vec3(0, 0, 1));


	StoreMeshData(GL_TRIANGLES);
}
