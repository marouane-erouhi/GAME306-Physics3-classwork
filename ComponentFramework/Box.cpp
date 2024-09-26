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
	// indecies define the faces
	int indices[6][6] = {
		{ 3,2,1,1,0,3},//front
		{ 7,4,5,5,6,7},//back
		{ 0,1,5,5,4,0},//bottom
		{ 7,6,2,2,3,7},//top
		{ 2,6,5,5,1,2},//left
		{ 7,3,0,0,4,7} //right
	};
	MATH::Vec3 localNormals[] = {
		MATH::Vec3(0, 0, -1),	// Back face normal		-z
		MATH::Vec3(0, 0, 1),	// Front face normal	+z
		MATH::Vec3(0, -1, 0),	// Bottom face normal	-y
		MATH::Vec3(0, 1, 0),	// Top face normal		+y
		MATH::Vec3(-1, 0, 0),	// Left face normal		-x
		MATH::Vec3(1, 0, 0)		// Right face normal	+x
	};

	for (int faceI = 0; faceI < 6; faceI++) {
		// for each face, push the 6 vertices
		for (int vertexI = 0; vertexI < 6; vertexI++) {
			auto vertexa = indices[faceI][vertexI];
			Vec3 vertex = center + multComponents(halfExtents, localVertices[indices[faceI][vertexI]]);
			vertex = QMath::rotate(vertex, orientation);
			vertices.push_back(vertex);
		}
		//Vec3 normal = QMath::rotate(localNormals[faceI], orientation);
		// TODO: do we need to rotate the normal s well?
		for (int i = 0; i < 6; i++) {
			//normals.push_back(normal);
			normals.push_back(localNormals[faceI]);
		}
	}

	// Use Triangle mode for the box
	StoreMeshData(GL_TRIANGLES);
}
