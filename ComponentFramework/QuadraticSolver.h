#pragma once
#include <stdio.h>
#include "Vector.h"

using namespace MATH;

namespace GEOMETRY {

	enum class NumSolutions {
		zero = 0,
		one,
		two
	};

	struct QuadraticSolution {
		NumSolutions numSolutions{ NumSolutions::zero };
		// I'll use first root as the smallest of the two. Set them both to zero to begin with
		float firstSolution = 0.0f;
		float secondSolution = 0.0f;

		void print() const;
	};

	QuadraticSolution solveQuadratic(float a, float b, float c);

}