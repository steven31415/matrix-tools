#include "matrix_tools.h"

bool testArrayEqual(int A[], int B[], size_t n);
void fourRussiansAccuracyTest(int minDimSize, int maxDimSize);
void fourRussiansTimingTest(int minDimSize, int maxDimSize);

// Test if two equal length arrays have the same contents
bool testArrayEqual(int A[], int B[], size_t n) {
	for (int i = 0; i < n; ++i) {
		if (A[i] != B[i]) {
			return false;
		}
	}

	return true;
}

// Compare results of fourRussiansSquareMultiply against naiveSquareMultiply
void fourRussiansAccuracyTest(int minDimSize, int maxDimSize) {
	for (int dimSize = minDimSize; dimSize <= maxDimSize; ++dimSize) {
		size_t arraySize = dimSize * dimSize;

		int A[arraySize], B[arraySize], C_fr[arraySize], C_naive[arraySize];

		// Fill A and B with randomly distributed booleans
		for (int i = 0; i < arraySize; ++i) {
			A[i] = rand() & 1;
			B[i] = rand() & 1;
		}
		
		// Apply both methods
		fourRussiansBooleanSquareMultiply(dimSize, A, B, C_fr);
		naiveSquareMultiply(dimSize, A, B, C_naive);

		// Print result of test
		printf("Dimension: %d\t%s\n", dimSize,
			testArrayEqual(C_fr, C_naive, arraySize) ? "Match": "Error");
	}
}

// Compare results of fourRussiansSquareMultiply against naiveSquareMultiply
void fourRussiansTimingTest(int minDimSize, int maxDimSize) {
	for (int dimSize = minDimSize; dimSize <= maxDimSize; ++dimSize) {
		size_t arraySize = dimSize * dimSize;

		int A[arraySize], B[arraySize], C_fr[arraySize], C_naive[arraySize];

		// Fill A and B with randomly distributed booleans
		for (int i = 0; i < arraySize; ++i) {
			A[i] = rand() & 1;
			B[i] = rand() & 1;
		}
		
		// Apply both methods
		fourRussiansBooleanSquareMultiply(dimSize, A, B, C_fr);
		naiveSquareMultiply(dimSize, A, B, C_naive);

		// Print result of test
		printf("Dimension: %d\t%s\n", dimSize,
			testArrayEqual(C_fr, C_naive, arraySize) ? "Match": "Error");
	}
}

int main() {

	fourRussiansAccuracyTest(0, 100);

	return 0;
}