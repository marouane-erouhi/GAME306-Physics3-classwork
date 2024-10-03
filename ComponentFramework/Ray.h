#pragma once
#include <Vector.h>
namespace GEOMETRY {

	struct RayIntersectionInfo {
		bool isIntersected = false;
		MATH::Vec3 intersectionPoint = MATH::Vec3();
		float t = 0.0f; // handy to know if we are going forward or backward
	};

	struct Ray {
		MATH::Vec3 start;
		MATH::Vec3 dir;
		Ray() {
			dir.x = 1;
		}
		Ray(const MATH::Vec3& start_, const MATH::Vec3& dir_)
			: start(start_)
			, dir(dir_) {
		}

		MATH::Vec3 currentPosition(float t) const {
			return start + t * dir;
		}

	};
}