#include "Cylinder.h"
#include <MMath.h>

using namespace MATH;
using namespace GEOMETRY;

inline static Vec3 perpendicular(const Vec3& dir) {
	/// The 0.01 added are for preventing division by zero
	// If dir is not parallel to the x-axis, choose (1, 0, 0) as the arbitrary vector
	if (fabs(dir.x) < fabs(dir.y) && fabs(dir.x) < fabs(dir.z)) {
		return VMath::normalize(VMath::cross(Vec3(1.0f, 0.01f, 0.01f), dir));
	}
	// If dir is not parallel to the y-axis, choose (0, 1, 0)
	else if (fabs(dir.y) < fabs(dir.x) && fabs(dir.y) < fabs(dir.z)) {
		return VMath::normalize(VMath::cross(Vec3(0.01f, 1.0f, 0.01f), dir));
	}
	// Otherwise, use (0, 0, 1) for the z-axis
	else {
		return VMath::normalize(VMath::cross(Vec3(0.01f, 0.01f, 1.0f), dir));
	}
}

// TODO: Cylinder seems to be missmatched with the model/texture
void GEOMETRY::Cylinder::generateVerticesAndNormals() {
	/*
	// We need to fill the vertices and normals arrays with the correct data for a sphere
	// deltaTheta governs how many points per ring. Try messing with it
	//const float deltaTheta = 5.0f;
	// deltaPhi governs how many rings there are in total.
	// Mar: this seems to me to determin the densitiy of the points along a circle
	const float deltaPhi = 10.0f;



	//Vec3 circle(r, 0.0f, 0.0f); // Initial point on the cap
	//Vec3 perp = perpendicular(dir); // Perpendicular vector to the axis

 i don't fully understand the use of perp vector
	for (int i = 0; i < numberOfCircles; i++) {
		for (float phiDeg = 0.0f; phiDeg <= 360.0f; phiDeg += deltaPhi) {
			// Rotate around the cylinder's axis
			Matrix3 rotationMatrix = MMath::rotate(phiDeg, dir);
			Vec3 rotatedPoint = rotationMatrix * (circle + perp); // Rotate around axis

			// Add the vertex
			vertices.push_back(capCenterPosA + dir * i * distanceBetweenCircles + rotatedPoint);

			// Add the normal
			normals.push_back(VMath::normalize(rotatedPoint)); // Normal points outwards
		}
	}
	*/


	// second attempt
	const float deltaTheta = 5.0f;
	float distanceBetweenCaps = VMath::distance(capCenterPosA, capCenterPosB);
	int numberOfCircles = 20; // how many circles between them?
	float distanceBetweenCircles = distanceBetweenCaps / numberOfCircles;

	Vec3 dir = VMath::normalize(capCenterPosB - capCenterPosA); // Axis direction

	for (int i = 0; i < numberOfCircles; i++) {

		for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta) {
			// Build a ring
			MATH::Vec3 circle(r * cos(thetaDeg * DEGREES_TO_RADIANS), r * sin(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
			// Push the circle point to our vertices array
			vertices.push_back(circle - (dir * distanceBetweenCircles * i));
			// The normal of a sphere points outwards from the center position Vec3(x, y, z)
			normals.push_back(circle); // will fix later
		}

	}


	StoreMeshData(GL_POINTS);
}

//void GEOMETRY::Cylinder::MakeCircle(float deltaTheta, Vec3& dir_, float distanceBetweenCircles, int currentCircle) {
//	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta) {
//		// Build a ring
//		MATH::Vec3 circle(r * cos(thetaDeg * DEGREES_TO_RADIANS), r * sin(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
//		// Push the circle point to our vertices array
//		vertices.push_back(circle + (dir_ * distanceBetweenCircles * currentCircle));
//		// The normal of a sphere points outwards from the center position Vec3(x, y, z)
//		normals.push_back(circle); // will fix later
//	}
//}

