#include "Box.h"
#include "QMath.h"
using namespace MATH;

MATH::Vec3 multComponents(MATH::Vec3 a, MATH::Vec3 b) {
	return MATH::Vec3(
		a.x * b.x,
		a.y * b.y,
		a.z * b.z
	);
}

void GEOMETRY::Box::generateVerticesAndNormals() {
	// Set up the eight vertices of the box
	MATH::Vec3 localVerticesOld[] = { // +x right - +y top - +z front
		MATH::Vec3(-1, -1, -1), // 0: Bottom-Left-Back
		MATH::Vec3(1, -1, -1),  // 1: Bottom-Right-Back
		MATH::Vec3(1, 1, -1),   // 2: Top-Right-Back
		MATH::Vec3(-1, 1, -1),  // 3: Top-Left-Back
		MATH::Vec3(-1, -1, 1),  // 4: Bottom-Left-Front		-x -y +z
		MATH::Vec3(1, -1, 1),   // 5: Bottom-Right-Front
		MATH::Vec3(1, 1, 1),    // 6: Top-Right-Front
		MATH::Vec3(-1, 1, 1)    // 7: Top-Left-Front
	};
	MATH::Vec3 localVertices[8] = { // +x right - +y top - +z front
		/*0*/MATH::Vec3(1,-1,1), // +-+
		/*1*/MATH::Vec3(-1,-1,1),//--+
		/*2*/MATH::Vec3(-1,1,1),//-++
		/*3*/MATH::Vec3(1,1,1),//+++
		/*4*/MATH::Vec3(1,-1,-1),//+--
		/*5*/MATH::Vec3(-1,-1,-1),//---
		/*6*/MATH::Vec3(-1,1,-1),//-+-
		/*7*/MATH::Vec3(1,1,-1)//++-
	};
	int indicesOld[6][6] = {
		{ 4, 5, 6, 6, 7, 4},	// Front	- bot tri	top tri		-- checked
		{ 0, 1, 2, 2, 3, 0},	// Back		- 
		{ 0, 1, 5, 5, 4, 0},	// Bottom
		{ 2, 3, 7, 7, 6, 2},	// Top
		{ 0, 3, 7, 7, 4, 0},	// Left
		{ 1, 2, 6, 6, 5, 1}		// Right
	};
	int indices[6][6] = {
		{ 3,2,1,1,0,3},//front
		{ 7,4,5,5,6,7},//back
		{ 0,1,5,5,4,0},//bottom
		{ 7,6,2,2,3,7},//top
		{ 2,6,5,5,1,2},//left
		{ 7,3,0,0,4,7} //right
	};

	MATH::Vec3 localNormals[] = {
		MATH::Vec3(0, 0, 1),	// 1 Front face normal		+z
		MATH::Vec3(0, 0, -1),	// 0 Back face normal		-z
		MATH::Vec3(0, -1, 0),	// 4 Bottom face normal		-y
		MATH::Vec3(0, 1, 0),	// 5 Top face normal		+y
		MATH::Vec3(-1, 0, 0),	// 2 Left face normal		-x
		MATH::Vec3(1, 0, 0)		// 3 Right face normal		+x
	};
	

	for (int faceI = 0; faceI < 6; faceI++) {
		// for each face, construct the 6 vertices
		for (int vertexI = 0; vertexI < 6; vertexI++) {
			auto vertexa = indices[faceI][vertexI];
			Vec3 vertex = center + multComponents(halfExtents, localVertices[indices[faceI][vertexI]]);
			vertex = QMath::rotate(vertex, orientation);
			vertices.push_back(vertex);
		}
		//Vec3 normal = QMath::rotate(localNormals[faceI], orientation);
		for (int i = 0; i < 6; i++) {
			//normals.push_back(normal);
			normals.push_back(localNormals[faceI]);
		}
	}


	//Vec3 topRightFront = center + Vec3(halfExtents.x, halfExtents.y, halfExtents.z);
	//topRightFront = QMath::rotate(topRightFront, orientation);

	//Vec3 topLeftFront = center + Vec3(-halfExtents.x, halfExtents.y, halfExtents.z);
	//topLeftFront = QMath::rotate(topLeftFront, orientation);

	//Vec3 bottomLeftFront = center + Vec3(-halfExtents.x, -halfExtents.y, halfExtents.z);
	//bottomLeftFront = QMath::rotate(bottomLeftFront, orientation);

	//// Let's make front face triangle 1 from the assignment doc
	//// Ask Scott if the winding order matters here
	//// Sam says anti-clockwise order so it wont backface cull
	//// Umer is doing anti-clockwise, so fingers crossed it works
	//vertices.push_back(topRightFront);
	//vertices.push_back(topLeftFront);
	//vertices.push_back(bottomLeftFront);
	//// All normals point along z for this triangle
	//normals.push_back(Vec3(0, 0, 1));
	//normals.push_back(Vec3(0, 0, 1));
	//normals.push_back(Vec3(0, 0, 1));


	StoreMeshData(GL_TRIANGLES);
}
