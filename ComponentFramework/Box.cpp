#include "Box.h"

void GEOMETRY::Box::generateVerticesAndNormals() {
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



	//StoreMeshData(GL_TRIANGLES);
}
