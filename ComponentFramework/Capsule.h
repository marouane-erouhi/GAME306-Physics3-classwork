#pragma once
#include "Shape.h"
#include <Vector.h>
#include <vector>
namespace GEOMETRY {
	struct Capsule : public Shape {
		float r = 1.0f;
		MATH::Vec3 sphereCentrePosA;
		MATH::Vec3 sphereCentrePosB;

		/// Just a little utility to populate a Sphere. The position of the centre of the sphere is the Vec3 inherited
		inline void set(float r_, MATH::Vec3 sphereCentrePosA_, MATH::Vec3 sphereCentrePosB_) {
			sphereCentrePosA = sphereCentrePosA_;
			sphereCentrePosB = sphereCentrePosB_;
			r = r_;

			generateVerticesAndNormals();
		}

		Capsule() = default;

		Capsule(float r, MATH::Vec3 sphereCentrePosA_, MATH::Vec3 sphereCentrePosB_) {
			set(r, sphereCentrePosA_, sphereCentrePosB_);
		}

		Capsule(const Capsule& s) {
			set(s.r, s.sphereCentrePosA, s.sphereCentrePosB);
		}

		/// print the values of the sphere and add a comment if you wish
		void print(const char* comment = nullptr) {
			if (comment) printf("%s\n", comment);
			printf("CapA:%f %f %f\t CapB:%f %f %f\t r:%f\n",
				sphereCentrePosA.x, sphereCentrePosA.y, sphereCentrePosA.z,
				sphereCentrePosB.x, sphereCentrePosB.y, sphereCentrePosB.z, r);
		}

		// TODO for assignment 2:
		// RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override;
		void generateVerticesAndNormals() override;
	};
}
