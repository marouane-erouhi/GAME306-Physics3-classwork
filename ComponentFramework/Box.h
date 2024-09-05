#pragma once
#include "Shape.h"
#include <Vector.h>
#include <vector>
#include <Quaternion.h>
namespace GEOMETRY {
	struct Box : public Shape {
		MATH::Vec3 center;
		MATH::Vec3 halfExtents;
		MATH::Quaternion orientation;

		/// Just a little utility to populate a Sphere. The position of the centre of the sphere is the Vec3 inherited
		inline void set(MATH::Vec3 center_, MATH::Vec3 halfExtents_, MATH::Quaternion orientation_) {
			center = center_;
			halfExtents = halfExtents_;
			orientation = orientation_;

			generateVerticesAndNormals();
		}

		Box() = default;

		Box(MATH::Vec3 center_, MATH::Vec3 halfExtents_, MATH::Quaternion orientation_) {
			set(center_, halfExtents_, orientation_);
		}

		Box(const Box& s) {
			set(s.center, s.halfExtents, s.orientation);
		}

		/// print the values of the sphere and add a comment if you wish
		void print(const char* comment = nullptr) {
			if (comment) printf("%s\n", comment);
			printf("Center:%f %f %f\t HalfExtents:%f %f %f\t Orientation:%f %f %f %f\n",
				center.x, center.y, center.z,
				halfExtents.x, halfExtents.y, halfExtents.z,
				orientation.w, orientation.ijk.x, orientation.ijk.y, orientation.ijk.z);
		}

		// TODO for assignment 2:
		// RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override;
		void generateVerticesAndNormals() override;
	};
}
