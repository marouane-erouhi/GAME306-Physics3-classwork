#include "Sphere.h"
#include <MMath.h>
#include "QuadraticSolver.h"

using namespace MATH;
using namespace GEOMETRY;

RayIntersectionInfo GEOMETRY::Sphere::rayIntersectionInfo(const Ray& ray) const {
	Vec3 D = ray.dir;
	Vec3 S = ray.start;
	Vec3 C = Vec3(x, y, z); // centre of sphere

	float a = VMath::dot(D, D); // D^2
	float b = 2 * (VMath::dot(S, D) - VMath::dot(S, C)); // 2(S dot D - D dot C)

	// S^2 - 2(S dot C) + C^2 - r^2 
	float c = VMath::dot(S, S) - (2 * VMath::dot(S, C)) + VMath::dot(C, C) - (r * r);

	QuadraticSolution sln = solveQuadratic(a, b, c);

	RayIntersectionInfo result{};
	// no intersection
	if (sln.numSolutions == NumSolutions::zero) {
		result.isIntersected = false;
		return result;
	}
	
	// there is an intersection
	// idk what to do with the other intersection
	// result.t would be the smallest positive solution
	result.isIntersected = true;
	result.t = sln.firstSolution;
	result.intersectionPoint = ray.currentPosition(result.t);

	return result;
}

void Sphere::generateVerticesAndNormals()
{
	// We need to fill the vertices and normals arrays with the correct data for a sphere
	// deltaTheta governs how many points per ring. Try messing with it
	const float deltaTheta = 5.0f;
	// deltaPhi governs how many rings there are in total. Try messing with it
	const float deltaPhi = 45.0f;
	// create points for the ring
	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta)
	{
		// Build a ring
		Vec3 circle(r * sin(thetaDeg * DEGREES_TO_RADIANS), r * cos(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		for (float phiDeg = 0.0f; phiDeg <= 360.0f; phiDeg += deltaPhi) {
			// Rotate a point in the ring around the y-axis to build a sphere!
			Matrix3 rotationMatrix = MMath::rotate(deltaPhi, Vec3(0.0f, 1.0f, 0.0f));
			circle = rotationMatrix * circle;
			// Push the circle point to our vertices array
			vertices.push_back(circle);
			// The normal of a sphere points outwards from the center position Vec3(x, y, z)
			normals.push_back(circle - Vec3(x, y, z));
		}
	}
	// Once we are all done filling the vertices and normals, use the base class method to store the data in the GPU
	StoreMeshData(GL_POINTS);
}