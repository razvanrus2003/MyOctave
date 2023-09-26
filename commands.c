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

void print_dimensions(long nr, long *m, long *n)
{
	long idx;
	scanf("%ld", &idx);
	if (valid_idx(idx, nr))
		error(-1);
	else
		printf("%ld %ld\n", m[idx], n[idx]);
}

void sort_mat_list(long *m, long *n, long nr, int ***mat)
{
	long *sum = alloc_vec(nr);
	if (!sum)
		my_exit(m, n, nr, mat);
	long i, j, k;
	// calculeaza suma fiecarei matrice in vectorul v
	for (i = 0; i < nr; i++)
		for (j = 0; j < m[i]; j++)
			for (k = 0; k < n[i]; k++) {
				sum[i] = (sum[i] + mat[i][j][k]) % NPRIM;
				if (sum[i] < 0)
					sum[i] += NPRIM;
			}
	// sorteaza tabloul in functie de sume
	for (i = 0; i < nr; i++)
		for (j = i + 1; j < nr; j++)
			if (sum[i] > sum[j]) {
				swap_mat(i, j, mat);
				swap_long(&sum[i], &sum[j]);
				swap_long(&m[i], &m[j]);
				swap_long(&n[i], &n[j]);
			}
	free(sum);
}

void cut_mat_command(long *m, long *n, long nr, int ***mat)
{
	long idx;
	scanf("%ld", &idx);
	if (valid_idx(idx, nr))
		error(-1);
	else
		if (cut_mat(&m[idx], &n[idx], &mat[idx]) == 0)
			my_exit(m, n, nr, mat);
}

void fold_command(long *nr, int ***mat, long *m, long *n)
{
	long idx, j;
	scanf("%ld", &idx);
	if (valid_idx(idx, *nr)) {
		error(-1);
	} else {
		free_mat(m[idx], mat[idx]);
		*nr -= 1;
		for (j = idx; j < *nr; j++) {
			mat[j] = mat[j + 1];
			m[j] = m[j + 1];
			n[j] = n[j + 1];
		}
		mat[j] = NULL;
	}
}

void power_command(long *m, long *n, long nr, int ***mat)
{
	long idx, pow;
	scanf("%ld %ld", &idx, &pow);
	if (valid_idx(idx, nr)) {
		error(-1);
	} else {
		if (pow < 0) {
			error(-3);
		} else {
			if (m[idx] != n[idx]) {
				error(-2);
			} else {
				mat[idx] = pow_mat(m[idx], mat[idx], pow);
				if (!mat[idx])
					my_exit(m, n, nr, mat);
			}
		}
	}
}

void load_command(long *m, long *n, long *nr, int ***mat)
{
	scanf("%ld %ld", &m[*nr], &n[*nr]);
	mat[*nr] = load_mat(m[*nr], n[*nr]);
	if (!mat[*nr]) {
		my_exit(m, n, *nr, mat);
	} else {
		read_mat(m[*nr], n[*nr], mat[*nr]);
		(*nr)++;
	}
}

void print_mat_command(long *m, long *n, long nr, int ***mat)
{
	long idx;
	scanf("%ld", &idx);
	if (valid_idx(idx, nr))
		error(-1);
	else
		print_mat(m[idx], n[idx], mat[idx]);
}

void trans_mat_command(long *m, long *n, long nr, int ***mat)
{
	long idx;
	scanf("%ld", &idx);
	if (valid_idx(idx, nr)) {
		error(-1);
	} else {
		mat[idx] = trans_mat(m[idx], n[idx], mat[idx]);
		if (!mat[idx])
			my_exit(m, n, nr, mat);
		swap_long(&m[idx], &n[idx]);
	}
}

void multiply_command(long *m, long *n, long *nr, int ***mat)
{
	long idx, idx_2;
	scanf("%ld %ld", &idx, &idx_2);
	if (valid_idx(idx, *nr) && valid_idx(idx_2, *nr)) {
		error(-1);
	} else {
		if (n[idx] != m[idx_2]) {
			error(-2);
		} else {
			mat[*nr] = mat_mult(m[idx], n[idx], n[idx_2], mat[idx], mat[idx_2]);
			if (!mat[*nr]) {
				my_exit(m, n, *nr, mat);
			} else {
				m[*nr] = m[idx];
				n[*nr] = n[idx_2];
				(*nr)++;
			}
		}
	}
}

void strassen_command(long *m, long *n, long *nr, int ***mat)
{
	long idx, idx_2;
	scanf("%ld %ld", &idx, &idx_2);
	if (valid_idx(idx, *nr) && valid_idx(idx_2, *nr)) {
		error(-1);
	} else {
		if (n[idx] != m[idx_2]) {
			error(-2);
		} else {
			mat[*nr] = strassen(m[idx], mat[idx], mat[idx_2]);
			if (!mat[*nr]) {
				my_exit(m, n, *nr, mat);
			} else {
				m[*nr] = m[idx];
				n[*nr] = n[idx_2];
				(*nr)++;
			}
		}
	}
}

// realoca spatiu pentru lista de matrice, dublandu-l
void extend_mat_list(long *size, long *nr, long **m, long **n, int ****mat)
{
	long *t;
	int ***tmp;
	*size *= 2;
	t = (long *)realloc(*m, sizeof(long) * (*size));
	if (!t)
		my_exit(*m, *n, *nr, *mat);
	*m = t;
	t = (long *)realloc(*n, sizeof(long) * (*size));
	if (!t)
		my_exit(*m, *n, *nr, *mat);
	*n = t;
	tmp = (int ***)realloc(*mat, (*size) * sizeof(int **));
	if (!tmp)
		my_exit(*m, *n, *nr, *mat);
	*mat = tmp;
}

// realoca spatiu pentru lista de matrice, injumatatindu-l
void retract_mat_list(long *size, long *nr, long **m, long **n, int ****mat)
{
	long *t;
	int ***tmp;
	*size /= 2;
	t = (long *)realloc(*m, sizeof(long) * (*size));
	if (!t)
		my_exit(*m, *n, *nr, *mat);
	*m = t;
	t = (long *)realloc(*n, sizeof(long) * (*size));
	if (!t)
		my_exit(*m, *n, *nr, *mat);
	*n = t;
	tmp = (int ***)realloc(*mat, (*size) * sizeof(int **));
	if (!tmp)
		my_exit(*m, *n, *nr, *mat);
	*mat = tmp;
}
