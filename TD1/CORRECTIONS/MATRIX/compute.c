/**
 * \file compute.c
 * \brief Allocate, multiply matrices and check_result
*/
#include <stdlib.h>
#include <stdio.h>
#include "compute.h"
#include "matrix.h"

/**
 * \brief Print PASSED if matrices are identical
 * \param v1 source matrix M1
 * \param v2 source matrix M2
 * \param dim dimension of square matrices
*/
static inline void print_results(double *m1,
				double *m2,
				unsigned int dim) {

	if(are_matrices_identical(m1, m2, dim)) {
		printf("PASSED\n");
	} else {
		printf("FAILED\n");
	}
}


/**
 * \brief Allocate, compute M3 += M1*M2, check result
 * \param dim dimension of square matrices
 * \param repeat repeat operation "repeat" times to get meaningful duration 
*/
void compute (unsigned int dim, unsigned int repeat) {
	double *M1, *M2, *M3;
	unsigned int i;
 
	M1 = allocate_square_matrix(dim);
	M2 = allocate_square_matrix(dim);
	M3 = allocate_square_matrix(dim);

	// Initialize each matrix
	init_square_matrix(M1, dim, 42.0);
	init_square_matrix_identity(M2, dim);
	init_square_matrix(M3, dim, 0.0);

	printf("Iteration: 1 + test... ");
	multiply_square_matrices(M3, M1, M2, dim);
	print_results(M1, M3, dim);

	for (i=0; i<repeat-1; i++) {
		printf("Iteration: %d\n", i+2);
		multiply_square_matrices(M3, M1, M2, dim);
	}

	free_square_matrix(&M1);
	free_square_matrix(&M2);
	free_square_matrix(&M3);
}
