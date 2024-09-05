#include "Cylinder.h"
#include <MMath.h>

using namespace MATH;
using namespace GEOMETRY;
// TODO: Cylinder seems to be missmatched with the model/texture
void GEOMETRY::Cylinder::generateVerticesAndNormals() {
	// We need to fill the vertices and normals arrays with the correct data for a sphere
	// deltaTheta governs how many points per ring. Try messing with it
	const float deltaTheta = 5.0f;
	// deltaPhi governs how many rings there are in total.
	// Mar: this seems to me to determin the densitiy of the points along a circle
	const float deltaPhi = 10.0f;

	// create circle
	// push vertices
	// move down a bit
	// repeat


	float distanceBetweenCaps = VMath::distance(capCenterPosA, capCenterPosB);
	// how many circles between them?
	int numberOfCircles = 5;

	// calculate the distance between each circle
	float distanceBetweenCircles = distanceBetweenCaps / numberOfCircles;

	Vec3 circle(r, r, 0.0);
	for (int i = 0; i < numberOfCircles; i++) {
		for (float phiDeg = 0.0f; phiDeg <= 360.0f; phiDeg += deltaPhi) {
			// Rotate a point in the ring around the y-axis to build a sphere!
			/// circle is just imaginary, every `deltaPhi` degrees, make that a point
			Matrix3 rotationMatrix = MMath::rotate(deltaPhi, Vec3(0.0f, 1.0f, 0.0f));
			/// rotate the circle by `deltaPhi`
			circle = rotationMatrix * circle;
			/// then sample that point and add to the vertices
			// Push the circle point to our vertices array
			vertices.push_back(circle);
			// The normal of a sphere points outwards from the center position Vec3(x, y, z)
			normals.push_back(circle - capCenterPosA);
		}
		// move the circle down by distanceBetweenCircles
		Matrix4 translationMatrix = MMath::translate(0.0f, distanceBetweenCircles, 0.0);
		circle = translationMatrix * Vec4(circle);
	}
	StoreMeshData(GL_POINTS);
}
