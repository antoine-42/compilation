/**
 * \file main.c
 * \brief main TD1 - part1 GCC
*/

#include <stdlib.h>
#include <stdio.h>
#include "compute.h"

#define MATRIX_DIM 1024
#define REPEAT (unsigned int)4

/**
 * \brief Print header and info
*/
void print_info() {
	printf("******************************************************\n");
	printf("          MIHPS - module CPA - TD1: part4 GPROF        \n");
	printf("   Multiply two square matrices                               \n");
	printf("   Square matrix dimension: %d\n", MATRIX_DIM);
	printf("   Repeat %u times\n", REPEAT);
	printf("******************************************************\n");
}


int main (int argc, char **argv) {
	print_info();

	compute(MATRIX_DIM, REPEAT);

	return 0;
}
