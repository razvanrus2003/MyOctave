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

// funtiile swap_... inverseaza diferite obiecte precum int-uri, matrice etc.
void swap_int(int *a, int *b)
{
	long aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void swap_long(long *a, long *b)
{
	long aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

int valid_idx(long idx, long nr)
{
	if (idx >= nr || idx < 0)
		return 1;
	return 0;
}

// copiaza coloana a din mat_1 in coloana b din mat_2
void cop_col(long m, long a, long b, int **mat_1, int **mat_2)
{
	int i;
	for (i = 0; i < m; i++)
		mat_2[i][b] = mat_1[i][a];
}

void swap_mat(long a, long b, int ***mat)
{
	int **aux;
	aux = mat[a];
	mat[a] = mat[b];
	mat[b] = aux;
}

// copiaza elementele unui matrice in alta
void cop_mat(long a, int **m, int **n)
{
	long i, j;
	for (i = 0; i < a; i++)
		for (j = 0; j < a; j++)
			m[i][j] = n[i][j];
}

// returneaza 0 daca caracterul citit nu reprezinta o comanda valida
int idf_char(char c)
{
	if (c < 'A' || c > 'Z')
		return 1;
	switch (c) {
	case 'Q':
	case 'L':
	case 'P':
	case 'R':
	case 'S':
	case 'D':
	case 'C':
	case 'M':
	case 'T':
	case 'O':
	case 'F':
	case '\n':
		return 1;
	default:
		return 0;
	}
}

// returneaza produsul a 2 matrice
int **mat_mult(long m, long n, long p, int **mat_1, int **mat_2)
{
	long tmp;
	int **mat_rez = load_mat(m, p);
	if (!mat_rez) {
		error(0);
		return NULL;
	}
	int i, j, k;
	for (i = 0; i < m; i++)
		for (j = 0; j < p; j++)
			for (k = 0; k < n; k++) {
				tmp = (mat_1[i][k] * mat_2[k][j]) % NPRIM;
				mat_rez[i][j] = (mat_rez[i][j] + tmp) % NPRIM;
				if (mat_rez[i][j] < 0)
					mat_rez[i][j] += NPRIM;
			}
	return mat_rez;
}

// returneaza produsul a 2 matrice cu scopul de a pune rezultatul in locul
// primei matrice
int **mat_mult_ovrr(long m, long n, long p, int **mat_1, int **mat_2)
{
	long tmp;
	int **mat_rez = load_mat(m, p);
	if (!mat_rez) {
		error(0);
		return NULL;
	}
	int i, j, k;
	for (i = 0; i < m; i++)
		for (j = 0; j < p; j++)
			for (k = 0; k < n; k++) {
				tmp = (mat_1[i][k] * mat_2[k][j]) % NPRIM;
				mat_rez[i][j] = (mat_rez[i][j] + tmp) % NPRIM;
				if (mat_rez[i][j] < 0)
					mat_rez[i][j] += NPRIM;
			}
	free_mat(n, mat_1);
	return mat_rez;
}

// returneaza transpusa unui matice
int **trans_mat(long m, long n, int **mat)
{
	int **tmp = load_mat(n, m);
	if (!tmp) {
		error(0);
		return tmp;
	}
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			tmp[j][i] = mat[i][j];
	free_mat(m, mat);
	return tmp;
}

// ridica o matice la o putere in timp logaritmic
int **pow_mat(long n, int **mat, long pw)
{
	int **tmp = load_mat(n, n);
	if (!tmp) {
		error(0);
		return tmp;
	}
	if (pw % 2 == 1) {
		cop_mat(n, tmp, mat);
		mat = pow_mat(n, mat, pw - 1);
		mat = mat_mult_ovrr(n, n, n, mat, tmp);
		free_mat(n, tmp);
		return mat;
	}
	if (pw == 2) {
		free_mat(n, tmp);
		return mat_mult_ovrr(n, n, n, mat, mat);
	}
	mat = pow_mat(n, mat, pw / 2);
	free_mat(n, tmp);
	return mat_mult_ovrr(n, n, n, mat, mat);
}

// executa operatia de taiere a unui matrice cu m linii si n coloane, returnand
// 0 daca au apurut probleme la alocarea si realocarea de spatiu;
int cut_mat(long *m, long *n, int ***mat)
{
	long *v = alloc_vec(*m);
	if (!v) {
		error(0);
		return 0;
	}
	long l, c, i, k;
	int **tmp;
	scanf("%ld", &l);
	tmp = (int **)malloc(l * sizeof(int *));
	if (!tmp) {
		error(0);
		return 0;
	}
	for (i = 0; i < l; i++) {
		scanf("%ld", &k);
		tmp[i] = (*mat)[k];
		v[k] = 1;
	}
	for (i = 0; i < *m; i++)
		if (!v[i]) {
			int *g = (*mat)[i];
			free(g);
		}
	free(*mat);
	*mat = tmp;
	*m = l;
	free(v);
	scanf("%ld", &c);
	tmp = load_mat(*m, c);
	if (!tmp)
		return 0;
	for (i = 0; i < c; i++) {
		scanf("%ld", &k);
		cop_col(*m, k, i, *mat, tmp);
	}
	free_mat(*m, *mat);
	*mat = tmp;
	*n = c;
	return 1;
}
