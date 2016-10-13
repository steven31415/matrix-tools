#ifndef MATRIX_TOOLS_
#define MATRIX_TOOLS_

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

double logbase (int x, int base);

void buildMatrix(	size_t inputSize, int input[],
					size_t output_xDimSize, size_t output_yDimSize, int output[][output_yDimSize],
					size_t format_xDimSize, size_t format_yDimSize);

void printMatrix(size_t xDimSize, size_t yDimSize, int A[][yDimSize], int padding);

void printArrayAsMatrix(size_t xDimSize, size_t yDimSize, int A[], int padding);

void naiveSquareMultiply(size_t dimSize, int A[], int B[], int C[]);

void fourRussiansBooleanSquareMultiply(size_t dimSize, int A[], int B[], int C[]);

#endif