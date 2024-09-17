#include "Box.h"
#include "QMath.h"

void GEOMETRY::Box::generateVerticesAndNormals() {
	/*
	MATH::Vec3 vertex0(-1.0f, -1.0f, -1.0f); // Front-Left-Bottom
	MATH::Vec3 vertex1(1.0f, -1.0f, -1.0f); // Front-Right-Bottom
	MATH::Vec3 vertex2(1.0f, 1.0f, -1.0f); // Back-Right-Bottom
	MATH::Vec3 vertex3(-1.0f, 1.0f, -1.0f); // Back-Left-Bottom
	MATH::Vec3 vertex4(-1.0f, -1.0f, 1.0f); // Front-Left-Top
	MATH::Vec3 vertex5(1.0f, -1.0f, 1.0f); // Front-Right-Top
	MATH::Vec3 vertex6(1.0f, 1.0f, 1.0f); // Back-Right-Top
	MATH::Vec3 vertex7(-1.0f, 1.0f, 1.0f); // Back-Left-Top

	// front tri 1---------
	vertices.push_back(vertex5);
	vertices.push_back(vertex4);
	vertices.push_back(vertex0);
	// front tri 2
	vertices.push_back(vertex0);
	vertices.push_back(vertex1);
	vertices.push_back(vertex5);

	// right tri 1------
	vertices.push_back(vertex7);
	vertices.push_back(vertex5);
	vertices.push_back(vertex1);
	// right tri 2
	vertices.push_back(vertex1);
	vertices.push_back(vertex3);
	vertices.push_back(vertex7);
	
	// back tri 1---------
	vertices.push_back(vertex6);
	vertices.push_back(vertex7);
	vertices.push_back(vertex3);
	// back tri 2
	vertices.push_back(vertex3);
	vertices.push_back(vertex2);
	vertices.push_back(vertex6);

	// left tri 1---------
	vertices.push_back(vertex4);
	vertices.push_back(vertex7);
	vertices.push_back(vertex3);
	// left tri 2
	vertices.push_back(vertex3);
	vertices.push_back(vertex0);
	vertices.push_back(vertex4);

	// bottom tri 1---------
	vertices.push_back(vertex1);
	vertices.push_back(vertex0);
	vertices.push_back(vertex3);
	// bottom tri 2
	vertices.push_back(vertex3);
	vertices.push_back(vertex2);
	vertices.push_back(vertex1);

	// top tri 1---------
	vertices.push_back(vertex6);
	vertices.push_back(vertex7);
	vertices.push_back(vertex4);
	// top tri 2
	vertices.push_back(vertex4);
	vertices.push_back(vertex5);
	vertices.push_back(vertex6);
	*/
	// -------------------
	// Define the vertices of the cube in local space
	std::vector<MATH::Vec3> localVertices = {
		MATH::Vec3(-1, -1, -1), MATH::Vec3(1, -1, -1), MATH::Vec3(1, 1, -1), MATH::Vec3(-1, 1, -1),
		MATH::Vec3(-1, -1, 1), MATH::Vec3(1, -1, 1), MATH::Vec3(1, 1, 1), MATH::Vec3(-1, 1, 1)
	};

	// Define the normals of the cube in local space
	MATH::Vec3 localNormals[] = {
		MATH::Vec3(0, 0, -1), MATH::Vec3(0, 0, 1), MATH::Vec3(-1, 0, 0), MATH::Vec3(1, 0, 0),
		MATH::Vec3(0, -1, 0), MATH::Vec3(0, 1, 0)
	};

	// Define the indices for the cube
	int indices[] = {
		0, 1, 2, 2, 3, 0,  // Front
		4, 5, 6, 6, 7, 4,  // Back
		0, 4, 5, 5, 1, 0,  // Bottom
		2, 6, 7, 7, 3, 2,  // Top
		0, 4, 7, 7, 3, 0,  // Left
		1, 5, 6, 6, 2, 1   // Right
	};

	// Transform the vertices and normals by the center, halfExtents and orientation
	for (int i = 0; i < 8; i++) {
		//MATH::Vec3 vertex = localVertices[i] * halfExtents + center;
		MATH::Vec3 vertex = MATH::Vec3();
		vertex.x = localVertices.at(i).x * halfExtents.x;
		vertex.y = localVertices.at(i).y * halfExtents.y;
		vertex.z = localVertices.at(i).z * halfExtents.z;
		vertex = vertex + center;

		MATH::Vec3 normal = MATH::QMath::rotate(localNormals[i % 6], orientation);
		MATH::VMath::normalize(normal);

		vertices.push_back(vertex);
		normals.push_back(normal);
	}

	// Add the vertices in the correct order (counter-clockwise)
	for (int i = 0; i < 36; i++) {
		vertices.push_back(vertices[indices[i]]);
		normals.push_back(normals[indices[i]]);
	}

	StoreMeshData(GL_TRIANGLES);
}
