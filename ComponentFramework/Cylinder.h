#pragma once
#include "Shape.h"
#include <Vector.h>
#include <vector>
namespace GEOMETRY {
	struct Cylinder : public Shape {
		float r = 1.0f;
		MATH::Vec3 capCenterPosA;
		MATH::Vec3 capCenterPosB;

		/// Just a little utility to populate a Sphere. The position of the centre of the sphere is the Vec3 inherited
		inline void set(float r_, MATH::Vec3 capCenterPosA_, MATH::Vec3 capCenterPosB_) {
			capCenterPosA = capCenterPosA_;
			capCenterPosB = capCenterPosB_;
			r = r_;

			generateVerticesAndNormals();
		}

		Cylinder() = default;

		Cylinder(float r, MATH::Vec3 capCenterPosA_, MATH::Vec3 capCenterPosB_) {
			set(r, capCenterPosA_, capCenterPosB_);
		}

		Cylinder(const Cylinder& s) {
			set(s.r, s.capCenterPosA, s.capCenterPosB);
		}

		/// print the values of the sphere and add a comment if you wish
		void print(const char* comment = nullptr) {
			if (comment) printf("%s\n", comment);
			printf("CapA:%f %f %f\t CapB:%f %f %f\t r:%f\n",	
				capCenterPosA.x, capCenterPosA.y, capCenterPosA.z, 
				capCenterPosB.x, capCenterPosB.y, capCenterPosB.z, r);
		}

		// TODO for assignment 2:
		// RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override;
		void generateVerticesAndNormals() override;
	};
}
