#ifndef __MATRIX__H
#define __MATRIX__H

double* allocate_square_matrix(unsigned int dim);

void init_square_matrix(double *matrix, 
			unsigned int dim, 
			double value);

void init_square_matrix_identity(double *matrix, 
			unsigned int dim);

void free_square_matrix(double **matrix);

void multiply_square_matrices(double *dest,
			double *src1, 
			double *src2,
			unsigned int dim);

int are_matrices_identical(double *m1, 
				double *m2,
				unsigned int dim);
#endif
