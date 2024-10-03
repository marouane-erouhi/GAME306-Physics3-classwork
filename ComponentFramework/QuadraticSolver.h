#pragma once
#include <stdio.h>

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

		void print() const {
			printf("Num of solutions: %d", (int)numSolutions);
			printf("\tSolution 1: %f.02\tSolution 2: %f.02\n", firstSolution, secondSolution);
		}
	};

	QuadraticSolution solveQuadratic(float a, float b, float c) {
		QuadraticSolution result{};
		float discriminant = b * b - 4 * a * c;
		if (discriminant < 0) {
			result.numSolutions = NumSolutions::zero;
			return result; // our default QuadraticSolution has no solutions
		}

		if (discriminant < VERY_SMALL || discriminant > -VERY_SMALL) {
			result.numSolutions = NumSolutions::one;
			// one solutions, since the ray is tangent to on side
			// In this case, we have one solution
			// so return a result with NumSolutions::one
			// and set firstSolution to -b / 2a
			// up to you what to do with secondSolution
			result.firstSolution = result.secondSolution = -b / (2*a);
			return result;
		}

		result.numSolutions = NumSolutions::two;
		// if u get here, the discriminant is positive
		// set both sollutions
		// the first solution is the nearer one - smallest, 
		// the second solution is larger - further (the opposite side of the object)
		float sln_1 = (-b + discriminant) / (2 * a);
		float sln_2 = (-b - discriminant) / (2 * a);

		// I'm not sure what to do when one sln is negetive and the other is positive
		if (sln_1 < sln_2) {
			result.firstSolution = sln_1;
			result.secondSolution = sln_2;
		} else {
			result.firstSolution = sln_2;
			result.secondSolution = sln_1;
		}
		return result;
	}

}