#include "Box.h"
#include "QMath.h"

void GEOMETRY::Box::generateVerticesAndNormals() {
	// Define the vertices of the cube in local space
	MATH::Vec3 localVertices[] = {
		MATH::Vec3(-1, -1, -1), // 0: Bottom-Left-Back
		MATH::Vec3(1, -1, -1),  // 1: Bottom-Right-Back
		MATH::Vec3(1, 1, -1),   // 2: Top-Right-Back
		MATH::Vec3(-1, 1, -1),  // 3: Top-Left-Back
		MATH::Vec3(-1, -1, 1),  // 4: Bottom-Left-Front
		MATH::Vec3(1, -1, 1),   // 5: Bottom-Right-Front
		MATH::Vec3(1, 1, 1),    // 6: Top-Right-Front
		MATH::Vec3(-1, 1, 1)    // 7: Top-Left-Front
	};
	// Define the normals of the cube in local space
	MATH::Vec3 localNormals[] = {
		MATH::Vec3(0, 0, -1),  // Back face normal
		MATH::Vec3(0, 0, 1),   // Front face normal
		MATH::Vec3(-1, 0, 0),  // Left face normal
		MATH::Vec3(1, 0, 0),   // Right face normal
		MATH::Vec3(0, -1, 0),  // Bottom face normal
		MATH::Vec3(0, 1, 0)    // Top face normal
	};
	int indices[] = {
		4, 5, 6, 6, 7, 4,  // Front (vertices 4, 5, 6, 7 form the front face)
		0, 1, 2, 2, 3, 0,  // Back  (vertices 0, 1, 2, 3 form the back face)
		0, 1, 5, 5, 4, 0,  // Bottom (vertices 0, 1, 5, 4 form the bottom face)
		2, 3, 7, 7, 6, 2,  // Top    (vertices 2, 3, 7, 6 form the top face)
		0, 3, 7, 7, 4, 0,  // Left   (vertices 0, 3, 7, 4 form the left face)
		1, 2, 6, 6, 5, 1   // Right  (vertices 1, 2, 6, 5 form the right face)
	};
	std::vector<MATH::Vec3> tempVertecies;
	std::vector<MATH::Vec3> tempNormals;

	// Transform the vertices and normals by the center, halfExtents and orientation
	for (int i = 0; i < 8; i++) {
		MATH::Vec3 vertex = MATH::Vec3(
			localVertices[i].x * halfExtents.x,
			localVertices[i].y * halfExtents.y,
			localVertices[i].z * halfExtents.z
		) + center;

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


	StoreMeshData(GL_TRIANGLES);
}
