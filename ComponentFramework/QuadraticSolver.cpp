#include "QuadraticSolver.h"

void GEOMETRY::QuadraticSolution::print() const {
	printf("Num of solutions: %d", (int)numSolutions);
	printf("\tSolution 1: %f.02\tSolution 2: %f.02\n", firstSolution, secondSolution);
}

GEOMETRY::QuadraticSolution GEOMETRY::solveQuadratic(float a, float b, float c) {
	QuadraticSolution result{};
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		result.numSolutions = NumSolutions::zero;
		return result;
	}

	if (fabs(discriminant) < VERY_SMALL) {  // Adjusted for floating-point precision check
		result.numSolutions = NumSolutions::one;
		result.firstSolution = -b / (2 * a);
		result.secondSolution = result.firstSolution;
		return result;
	}

	// if u get here, the discriminant is positive
	// set both sollutions
	// the first solution is the nearer one - smallest, 
	// the second solution is larger - further (the opposite side of the object)
	result.numSolutions = NumSolutions::two;
	float sqrtDiscriminant = sqrt(discriminant);
	float sln_1 = (-b + sqrtDiscriminant) / (2 * a);//nearSolution
	float sln_2 = (-b - sqrtDiscriminant) / (2 * a);//farSolution

	if (sln_1 < sln_2) {
		result.firstSolution = sln_1;
		result.secondSolution = sln_2;
	} else {
		result.firstSolution = sln_2;
		result.secondSolution = sln_1;
	}

	return result;
}
