#include "matrix_tools.h"

double logbase (int x, int base) {
	double lg;
	lg = (double) log10(x) / log10(base);
	return(lg);
}

void buildMatrix(	size_t inputSize, int input[],
					size_t output_xDimSize, size_t output_yDimSize, int output[][output_yDimSize],
					size_t format_xDimSize, size_t format_yDimSize) {

	int readPos = 0;

	for (int i = 0; i < output_xDimSize; ++i) {
		for (int j = 0; j < output_yDimSize; ++j) {
			if (i >= format_xDimSize || j >= format_yDimSize) {
				output[i][j] = 0;
			}
			else {
				readPos = i * format_yDimSize + j;

				if (readPos < inputSize) {
					output[i][j] = input[readPos];
				}
				else {
					output[i][j] = 0;
				}
			}
		}
	}
}

void printMatrix(size_t xDimSize, size_t yDimSize, int A[][yDimSize], int padding) {
	for (int i = 0; i < xDimSize; ++i) {
		for (int j = 0; j < yDimSize; ++j) {
			printf (" %0*d ", padding, A[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

void printArrayAsMatrix(size_t xDimSize, size_t yDimSize, int A[], int padding) {
	for (int i = 0; i < xDimSize; ++i) {
		for (int j = 0; j < yDimSize; ++j) {
			printf (" %0*d ", padding, A[i * yDimSize + j]);
		}
		printf("\n");
	}

	printf("\n");
}

void naiveSquareMultiply(size_t dimSize, int A[], int B[], int C[]) {
	for (int i = 0; i < dimSize * dimSize; ++i) {
		C[i] = 0;
	}

	for (int i = 0; i < dimSize; ++i) {
		for (int j = 0; j < dimSize; ++j) {
			for (int k = 0; k < dimSize; ++k) {
				C[i * dimSize + j] += A[i * dimSize + k] * B[j + k * dimSize];
			}
		}
	}
}

// Worst-Case Complexity: O(n^3 / log(n)) where n = dimSize
void fourRussiansBooleanSquareMultiply(size_t dimSize, int A[], int B[], int C[]) {

	// O(1)
	int sliceSize = floor(logbase(dimSize, 2));
	int sliceCount = ceil((double) dimSize / sliceSize);
	int paddedSize = sliceSize * sliceCount;
	int wordCount = pow(2, sliceSize);

	// O(n^2)
	int (*hash)[dimSize] = malloc(sizeof(int[wordCount][dimSize]));

	// O(n)
	for (int i = 0; i < dimSize; ++i) {
		hash[0][i] = 0;
	}

	// O(n^2)
	for (int i = 0; i < dimSize * dimSize; ++i) {
		C[i] = 0;
	}

	// O(n^2)
	int (*A_m)[paddedSize] = malloc(sizeof(int[dimSize][paddedSize]));
	int (*B_m)[dimSize] = malloc(sizeof(int[paddedSize][dimSize]));

	// O(n^2)
	buildMatrix(dimSize * dimSize, A, dimSize, paddedSize, A_m, dimSize, dimSize);
	buildMatrix(dimSize * dimSize, B, paddedSize, dimSize, B_m, dimSize, dimSize);

	// Helper Function - O(n)
	// Calculate hash array for single slice of four russians method
	void calculateHash(	size_t B_yDimSize, int B[][B_yDimSize],
						int value, int hash[][B_yDimSize],
						int slice, int sliceSize) {

		// O(1)
		int sigBitIndex = (int) logbase (value, 2);
		int valueWithoutSigBit = value - pow(2, sigBitIndex);

		// O(n)
		for (int i = 0; i < B_yDimSize; ++i) {
			hash[value][i] = hash[valueWithoutSigBit][i]
				+ B[(sliceSize - sigBitIndex - 1) + (slice * sliceSize)][i];
		}
	}

	// Helper Function - O(log(n))
	// Convert boolean array slice to corresponding integer
	int getBinaryValue(int array[], int start, size_t n) {
		// O(1)
		int value = 0;
		int multiplier = 1;

		// O(log(n))
		for (int i = start + n - 1; i >= start; --i) {
			value += multiplier * array[i];
			multiplier *= 2;
		}

		return value;
	}

	// Loop: O((n / log(n)) * n^2) = O(n^3 / log(n))
	for (int slice = 0; slice < sliceCount; ++slice) {

		// Loop: O(n^2)
		for (int value = 1; value < wordCount; ++value) {
			// O(n)
			calculateHash(dimSize, B_m, value, hash, slice, sliceSize);
		}

		// Loop: O(n * (n + log(n))) = O(n^2)
		for (int a_row = 0; a_row < dimSize; ++a_row) {
			// O(log(n))
			int value = getBinaryValue(A_m[a_row], slice * sliceSize, sliceSize);

			// O(n)
			for (int i = 0; i < dimSize; ++i) {
				C[a_row * dimSize + i] += hash[value][i];
			}
		}
	}

	free(A_m);
	free(B_m);
	free(hash);
}
