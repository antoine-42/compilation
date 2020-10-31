/**
 * \file matrix.c
 * \brief Matrix operationsi
 * Source of blocked dgemm : http://www.eecs.berkeley.edu/~knight/cs267/hw1/dgemm-blocked.c
*/
#include "matrix.h"
#include "malloc.h"

#define BLOCK_SIZE 32
#define min(a,b) (((a)<(b))?(a):(b))

/**
 * \brief Allocate a square matrix with the specified dimension
 * \param dim dimension of the square matrix
 * \return ptr to the allocated matrix
*/
double* allocate_square_matrix(unsigned int dim) {
	double *vector;
	vector = (double*) malloc(sizeof(double)*dim*dim);

	return vector;
}


/**
 * \brief Free an allocated matrix and set its pointer to NULL
 * \param matrix ptr of ptr to the matrix
*/
void free_square_matrix(double **matrix) {
	free(*matrix);
	*matrix = NULL;
}


/**
 * \brief Initialize a square matrix with one value
 * \param matrix matrix to initialize
 * \param dim dimension of the square matrix
 * \param value value to set
*/
void init_square_matrix(double *matrix, 
			unsigned int dim,
			double value) {

	unsigned int i;

	for (i=0; i<dim*dim; i++) {
		matrix[i] = value;
	}
}


/**
 * \brief Initialize an identity matrix
 * \param matrix matrix to initialize
 * \param dim dimension of the square matrix
*/
void init_square_matrix_identity(double *matrix, 
			unsigned int dim) {

	unsigned int i,j;

	for (i=0; i<dim; i++) {
		for (j=0; j<dim; j++) {
			if (i==j) {
				matrix[i*dim+j] = 1.0;
			} else {
				matrix[i*dim+j] = 0.0;
			}
		}
	}
}


/**
 * \brief Multiply two square matrices and store result in a third one
 * \param dest matrix where results are stored
 * \param src1 matrix 1
 * \param src2 matrix 2
 * \param dim dimension of square matrices
*/
static inline void multiply_square_matrices_simple(double *dest,
			double *src1, 
			double *src2,
			unsigned int dim) {
	unsigned int i,j,k;

	for (i=0; i<dim; i++) {
		for (j=0; j<dim; j++) {
			double tempo = 0;
			for (k=0; k<dim; k++) {
				tempo += src1[i*dim+k]*src2[k*dim+j];
			}
			dest[i*dim+j] += tempo;
		}
	} 
}


/**
 * \brief performs a smaller dgemm operation C := C + A * B
 * \param lda stride
 * \param M M dimension
 * \param N N dimension
 * \param K K dimension
 * \param C M-by-N matrix
 * \param A M-by-K matrix
 * \param B K-by-N matrix
*/
static inline void do_block (int lda, int M, int N, int K, double* A, double* B, double* C) {	
	unsigned int i, j, k;
	/* For each row i of A */
	for (i = 0; i < M; ++i)
		/* For each column j of B */ 
		for (j = 0; j < N; ++j) {
			/* Compute C(i,j) */
			double cij = C[i+j*lda];
			for (k = 0; k < K; ++k)
				cij += A[i+k*lda] * B[k+j*lda];
			C[i+j*lda] = cij;
		}
}


/**
 * \brief performs a dgemm operation (matrix multiply) on square matrices
 * \param C dest matrix
 * \param A src matrix
 * \param B src matrix
 * \param lda dimension of matrices
*/
static inline void  multiply_square_matrices_tiled (double* C, double* A, double* B, unsigned int lda) {
	unsigned int i,j,k;
  for (i = 0; i < lda; i += BLOCK_SIZE)
    for (j = 0; j < lda; j += BLOCK_SIZE)
      for (k = 0; k < lda; k += BLOCK_SIZE) {
	/* Correct block dimensions if block "goes off edge of" the matrix */
	int M = min (BLOCK_SIZE, lda-i);
	int N = min (BLOCK_SIZE, lda-j);
	int K = min (BLOCK_SIZE, lda-k);

	/* Perform individual block dgemm */
	do_block(lda, M, N, K, A + i + k*lda, B + k + j*lda, C + i + j*lda);
      }
}


/**
 * \brief check if two matrices are identical
 * \param m1 matrix 1
 * \param m2 matrix 2
 * \param dim dimension of matrices
*/
int are_matrices_identical(double *m1, 
				double *m2,
				unsigned int dim) {

	unsigned int i,j;

	for (i=0; i<dim; i++) {
		for (j=0; j<dim; j++) {
			if (m1[i*dim+j] != m2[i*dim+j]) return 0;
		}
	}
	return 1;	
}


/**
 * \brief multiply two matrices
 * \param dest destination matrix
 * \param src1 source matrix 2
 * \param src2 source matrix 2
 * \param dim dimension of matrices
*/
void multiply_square_matrices(double *dest,
			double *src1, 
			double *src2,
			unsigned int dim) {

#ifdef TILED
	multiply_square_matrices_tiled(dest, src1, src2, dim);
#else
	multiply_square_matrices_simple(dest, src1, src2, dim);
#endif
}
