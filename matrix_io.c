// Copyright Razvan-Constantin Rus 312CAa 2022-2023
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "matrix_io.h"
#include "dinall_matrix.h"
#include "functions.h"
#include "strassen.h"
#include "commands.h"

#define NPRIM 10007

// citeste elementele unei matrice cu m linii si n coloane
void read_mat(long m, long n, int **mat)
{
	long i, j;
	int c;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			scanf("%d", &c);
			mat[i][j] = c;
		}
}

// afisea continutul unei matice
void print_mat(long m, long n, int **mat)
{
	long i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}
