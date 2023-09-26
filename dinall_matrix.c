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

// aloca spatiu pentru un vector cu n elemente
long *alloc_vec(long n)
{
	long *v = (long *)calloc(n, sizeof(long));
	if (!(v)) {
		error(0);
		return NULL;
	}
	return v;
}

// aloca spatiu pentru o matice cu m linii si n coloane
int **load_mat(long m, long n)
{
	int **mat;
	long i = 0;
	mat = (int **)calloc(m, sizeof(int *));
	if (!(mat)) {
		error(0);
		return NULL;
	}
	for (i = 0; i < m; i++) {
		mat[i] = (int *)calloc(n, sizeof(int));
		if (!(mat)) {
			error(0);
			return NULL;
		}
	}
	return mat;
}

// elibereaza spatiul ocupat de o matrice
void free_mat(long m, int **mat)
{
	if (mat) {
		long i;
		for (i = 0; i < m; i++)
			free(mat[i]);
		free(mat);
	}
}

// este folosita a eliberarea spatiului alocat la terminarea programului
void free_all(long *m, long *n, long size, int ***mat)
{
	long i;
	if (mat) {
		for (i = 0; i < size; i++)
			if (mat[i])
				free_mat(m[i], mat[i]);
		free(mat);
	}
	if (m)
		free(m);
	if (n)
		free(n);
}

// aloca spatiu pentru tablouri la inceputul programului
void init_alloc(long size, int ****mat, long **m, long **n)
{
	*mat = (int ***)calloc(size, sizeof(int **));
	if (!(*mat)) {
		error(0);
		exit(0);
	}
	*m = (long *)calloc(size, sizeof(long));
	if (!(*m)) {
		error(0);
		free(*mat);
		exit(0);
	}
	*n = (long *)calloc(size, sizeof(long));
	if (!(*n)) {
		error(0);
		free(*mat);
		free(*m);
		exit(0);
	}
}

void my_exit(long *m, long *n, long nr, int ***mat)
{
	error(0);
	free_all(m, n, nr, mat);
	exit(0);
}
