#include "Capsule.h"
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

void GEOMETRY::Capsule::generateVerticesAndNormals() {
	const float deltaTheta = 5.0f; //how many points per ring
	const float deltaPhi = 5.0f; //how many rings

	Vec3 dir = VMath::normalize(sphereCentrePosB - sphereCentrePosA); // Axis direction

	// half sphere 1 ------------------------
	for (float thetaDeg = 0.0f; thetaDeg <= 90.0f; thetaDeg += deltaTheta) {
		// Build a ring
		Vec3 circle(r * sin(thetaDeg * DEGREES_TO_RADIANS), r * cos(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		for (float phiDeg = 0.0f; phiDeg <= 360.0f; phiDeg += deltaPhi) {
			// Rotate a point in the ring around the y-axis to build a sphere!
			//Matrix3 rotationMatrix = MMath::rotate(deltaPhi, Vec3(0.0f, 1.0f, 0.0f));
			Matrix3 rotationMatrix = MMath::rotate(deltaPhi, dir);
			circle = rotationMatrix * circle;
			// Push the circle point to our vertices array
			vertices.push_back(circle + sphereCentrePosA);
			// The normal of a sphere points outwards from the center position Vec3(x, y, z)
			normals.push_back(circle - Vec3(sphereCentrePosA.x, sphereCentrePosA.y, sphereCentrePosA.z));


		}
	}
	// half sphere 2 ------------------------
	for (float thetaDeg = 90.0f; thetaDeg <= 180.0f; thetaDeg += deltaTheta) {
		// Build a ring
		Vec3 circle(r * sin(thetaDeg * DEGREES_TO_RADIANS), r * cos(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		for (float phiDeg = 0.0f; phiDeg <= 360.0f; phiDeg += deltaPhi) {
			// Rotate a point in the ring around the y-axis to build a sphere!
			//Matrix3 rotationMatrix = MMath::rotate(deltaPhi, Vec3(0.0f, 1.0f, 0.0f));
			Matrix3 rotationMatrix = MMath::rotate(deltaPhi, dir);
			circle = rotationMatrix * circle;
			// Push the circle point to our vertices array
			vertices.push_back(circle + sphereCentrePosB);
			// The normal of a sphere points outwards from the center position Vec3(x, y, z)
			normals.push_back(circle - Vec3(sphereCentrePosB.x, sphereCentrePosB.y, sphereCentrePosB.z));
		}
	}

	// cylinder in the middle
	float distanceBetweenCaps = VMath::distance(sphereCentrePosA, sphereCentrePosB);
	int numberOfCircles = 20; // how many circles between them?
	float distanceBetweenCircles = distanceBetweenCaps / numberOfCircles;

	Vec3 circle(r, 0.0f, 0.0f); // Initial point on the cap
	Vec3 perp = perpendicular(dir); // Perpendicular vector to the axis

	for (int i = 0; i < numberOfCircles; i++) {
		for (float phiDeg = 0.0f; phiDeg <= 360; phiDeg += deltaPhi) {
			// Rotate around the cylinder's axis
			Matrix3 rotationMatrix = MMath::rotate(phiDeg, dir);
			Vec3 rotatedPoint = rotationMatrix * circle;//(circle + perp); // Rotate around axis

			// Add the vertex
			vertices.push_back(rotatedPoint + sphereCentrePosA + dir * i * distanceBetweenCircles);

			// Add the normal
			normals.push_back(VMath::normalize(rotatedPoint)); // Normal points outwards
		}
	}

	StoreMeshData(GL_POINTS);

	/*

	std::cout << "r: " << r << "\ta: " << sphereCentrePosA << "\tb: " << sphereCentrePosB << "\n";

	*/
}
