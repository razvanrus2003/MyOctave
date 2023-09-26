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

int **strassen(long n, int **mat_1, int **mat_2);

void squad_free(long n, int **a, int **b, int **c, int **d)
{
	free_mat(n, a);
	free_mat(n, b);
	free_mat(n, c);
	free_mat(n, d);
}

void trio_free(long n, int **a, int **b, int **c)
{
	free_mat(n, a);
	free_mat(n, b);
	free_mat(n, c);
}

// returneaza suma a 2 matrice
int **sum_mat(long n, int **a, int **b)
{
	long i, j;
	int **sum = load_mat(n, n);
	if (!sum)
		return sum;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sum[i][j] = (a[i][j] + b[i][j]) % NPRIM;
			if (sum[i][j] < 0)
				sum[i][j] += NPRIM;
		}
	}
	return sum;
}

// returneaza suma a 2 matrice cu scopul de a pune rezultatul in locul
// primei matrice
int **sum_mat_ovrr(long n, int **a, int **b)
{
	long i, j;
	int **sum = load_mat(n, n);
	if (!sum)
		return sum;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sum[i][j] = (a[i][j] + b[i][j]) % NPRIM;
			if (sum[i][j] < 0)
				sum[i][j] += NPRIM;
		}
	}
	free_mat(n, a);
	return sum;
}

// returneaza diferenta a 2 matrice
int **dif_mat(long n, int **a, int **b)
{
	long i, j;
	int **sum = load_mat(n, n);
	if (!sum)
		return sum;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sum[i][j] = (a[i][j] - b[i][j]) % NPRIM;
			if (sum[i][j] < 0)
				sum[i][j] += NPRIM;
		}
	}

	return sum;
}

// returneaza diferenta a 2 matrice cu scopul de a pune rezultatul in locul
// primei matrice
int **dif_mat_ovrr(long n, int **a, int **b)
{
	long i, j;
	int **sum = load_mat(n, n);
	if (!sum)
		return sum;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sum[i][j] = (a[i][j] - b[i][j]) % NPRIM;
			if (sum[i][j] < 0)
				sum[i][j] += NPRIM;
		}
	}
	free_mat(n, a);
	return sum;
}

// returneaza unul din cadranele unei matrice in functie de variabila c
int **matrix_divider(int **mat, long n, int c)
{
	long i, j;
	int **rez = load_mat(n / 2, n / 2);
	if (!rez)
		return rez;
	if (c == 1)
		for (i = 0; i < n / 2; i++)
			for (j = 0; j < n / 2; j++)
				rez[i][j] = mat[i][j];
	if (c == 2)
		for (i = 0; i < n / 2; i++)
			for (j = n / 2; j < n; j++)
				rez[i][j - n / 2] = mat[i][j];
	if (c == 3)
		for (i = n / 2; i < n; i++)
			for (j = 0; j < n / 2; j++)
				rez[i - n / 2][j] = mat[i][j];
	if (c == 4)
		for (i = n / 2; i < n; i++)
			for (j = n / 2; j < n; j++)
				rez[i - n / 2][j - n / 2] = mat[i][j];
	return rez;
}

// functiile m_alloc_x returneaza fiecare din matricele m1...m7
int **m_alloc_1(long n, int **a, int **d, int **x, int **t)
{
	if (n == 1) {
		int **rez = load_mat(1, 1);
		if (!rez)
			return NULL;
		rez[0][0] = (a[0][0] + d[0][0]) * (x[0][0] + t[0][0]);
		return rez;
	}
	int **rez;
	int **u, **v;
	u = sum_mat(n, a, d);
	if (!u)
		return NULL;
	v = sum_mat(n, x, t);
	if (!v)
		return NULL;
	rez = strassen(n, u, v);
	free_mat(n, u);
	free_mat(n, v);
	return rez;
}

int **m_alloc_2(long n, int **c, int **d, int **x)
{
	if (n == 1) {
		int **rez = load_mat(1, 1);
		if (!rez)
			return NULL;
		rez[0][0] = (c[0][0] + d[0][0]) * x[0][0];
		return rez;
	}
	int **rez;
	int **u;
	u = sum_mat(n, c, d);
	if (!u)
		return NULL;
	rez = strassen(n, u, x);
	free_mat(n, u);
	return rez;
}

int **m_alloc_3(long n, int **a, int **y, int **t)
{
	if (n == 1) {
		int **rez = load_mat(1, 1);
		if (!rez)
			return NULL;
		rez[0][0] = a[0][0] * (y[0][0] - t[0][0]);
		return rez;
	}
	int **rez;
	int **u;
	u = dif_mat(n, y, t);
	if (!u)
		return NULL;
	rez = strassen(n, a, u);
	free_mat(n, u);
	return rez;
}

int **m_alloc_4(long n, int **d, int **z, int **x)
{
	if (n == 1) {
		int **rez = load_mat(1, 1);
		if (!rez)
			return NULL;
		rez[0][0] = d[0][0] * (z[0][0] - x[0][0]);
		return rez;
	}
	int **rez;
	int **u;
	u = dif_mat(n, z, x);
	if (!u)
		return NULL;
	rez = strassen(n, d, u);
	free_mat(n, u);
	return rez;
}

int **m_alloc_5(long n, int **a, int **b, int **t)
{
	if (n == 1) {
		int **rez = load_mat(1, 1);
		if (!rez)
			return NULL;
		rez[0][0] = (a[0][0] + b[0][0]) * t[0][0];
		return rez;
	}
	int **rez;
	int **u;
	u = sum_mat(n, a, b);
	if (!u)
		return NULL;
	rez = strassen(n, u, t);
	free_mat(n, u);
	return rez;
}

int **m_alloc_6(long n, int **c, int **a, int **x, int **y)
{
	if (n == 1) {
		int **rez = load_mat(1, 1);
		if (!rez)
			return NULL;
		rez[0][0] = (c[0][0] - a[0][0]) * (x[0][0] + y[0][0]);
		return rez;
	}
	int **rez;
	int **u, **v;
	u = dif_mat(n, c, a);
	if (!u)
		return NULL;
	v = sum_mat(n, x, y);
	if (!v)
		return NULL;
	rez = strassen(n, u, v);
	free_mat(n, u);
	free_mat(n, v);
	return rez;
}

int **m_alloc_7(long n, int **b, int **d, int **z, int **t)
{
	if (n == 1) {
		int **rez = load_mat(1, 1);
		if (!rez)
			return NULL;
		rez[0][0] = (b[0][0] - d[0][0]) * (z[0][0] + t[0][0]);
		return rez;
	}
	int **rez;
	int **u, **v;
	u = dif_mat(n, b, d);
	if (!u)
		return NULL;
	v = sum_mat(n, z, t);
	if (!v)
		return NULL;
	rez = strassen(n, u, v);
	free_mat(n, u);
	free_mat(n, v);
	return rez;
}

// returneaza o matice mai mare din 4 mai mici
int **matrix_constructor(long n, int **a, int **b, int **c, int **d)
{
	long i, j;
	int **rez = load_mat(n, n);
	if (!rez)
		return rez;
	for (i = 0; i < n / 2; i++)
		for (j = 0; j < n / 2; j++)
			rez[i][j] = a[i][j];
	for (i = 0; i < n / 2; i++)
		for (j = n / 2; j < n; j++)
			rez[i][j] = b[i][j - n / 2];
	for (i = n / 2; i < n; i++)
		for (j = 0; j < n / 2; j++)
			rez[i][j] = c[i - n / 2][j];
	for (i = n / 2; i < n; i++)
		for (j = n / 2; j < n; j++)
			rez[i][j] = d[i - n / 2][j - n / 2];
	squad_free(n / 2, a, b, c, d);
	return rez;
}

// imparte maticea in 4 mai mici
int general_mat_div(long n, int ***a, int ***b, int ***c, int ***d, int **mat)
{
	*a = matrix_divider(mat, n, 1);
	*b = matrix_divider(mat, n, 2);
	*c = matrix_divider(mat, n, 3);
	*d = matrix_divider(mat, n, 4);
	if (!*a || !*b || !*c || !*d) {
		squad_free(n / 2, *a, *b, *c, *d);
		return 0;
	}
	return 1;
}

int **strassen(long n, int **mat_1, int **mat_2)
{
	int **a, **b, **c, **d;
	int **x, **y, **z, **t;
	int **m_1, **m_2, **m_3, **m_4, **m_5, **m_6, **m_7;
	if (general_mat_div(n, &a, &b, &c, &d, mat_1) == 0)
		return NULL;
	if (general_mat_div(n, &x, &y, &z, &t, mat_2) == 0) {
		squad_free(n / 2, a, b, c, d);
		return NULL;
	}
	m_1 = m_alloc_1(n / 2, a, d, x, t);
	m_2 = m_alloc_2(n / 2, c, d, x);
	m_3 = m_alloc_3(n / 2, a, y, t);
	m_4 = m_alloc_4(n / 2, d, z, x);
	m_5 = m_alloc_5(n / 2, a, b, t);
	m_6 = m_alloc_6(n / 2, c, a, x, y);
	m_7 = m_alloc_7(n / 2, b, d, z, t);
	squad_free(n / 2, a, b, c, d);
	squad_free(n / 2, x, y, z, t);
	if (!m_1 || !m_2 || !m_3 || !m_4 || !m_5 || !m_6 || !m_7) {
		squad_free(n / 2, m_1, m_2, m_3, m_4);
		trio_free(n / 2, m_5, m_6, m_7);
		return NULL;
	}
	a = sum_mat(n / 2, m_1, m_4);
	a = dif_mat_ovrr(n / 2, a, m_5);
	a = sum_mat_ovrr(n / 2, a, m_7);
	b = sum_mat(n / 2, m_3, m_5);
	c = sum_mat(n / 2, m_2, m_4);
	d = dif_mat(n / 2, m_1, m_2);
	d = sum_mat_ovrr(n / 2, d, m_3);
	d = sum_mat_ovrr(n / 2, d, m_6);
	if (!a || !b || !c || !d) {
		squad_free(n / 2, a, b, c, d);
		return NULL;
	}
	squad_free(n / 2, m_1, m_2, m_3, m_4);
	trio_free(n / 2, m_5, m_6, m_7);
	return matrix_constructor(n, a, b, c, d);
}
