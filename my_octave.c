// Copyright Razvan-Constantin Rus 312CAa 2022-2023
#include <stdio.h>
#include <stdlib.h>

#define NPRIM 10007

#include "error.h"
#include "matrix_io.h"
#include "dinall_matrix.h"
#include "functions.h"
#include "strassen.h"
#include "commands.h"

int main(void)
{
	// lista de matrice
	int ***mat;
	// in vectorii m si n retinem dimensiunile matricelor din lista
	long *m, *n;
	// nr este numarul de matrice din lista si size este dimensiunea listei
	long nr = 0, size = 2;
	char c;
	init_alloc(size, &mat, &m, &n);
	do {
		scanf("%c", &c);
		if (c == 'L')
			load_command(m, n, &nr, mat);
		if (c == 'P')
			print_mat_command(m, n, nr, mat);
		if (c == 'C')
			cut_mat_command(m, n, nr, mat);
		if (c == 'S')
			strassen_command(m, n, &nr, mat);
		if (c == 'M')
			multiply_command(m, n, &nr, mat);
		if (c == 'D')
			print_dimensions(nr, m, n);
		if (c == 'T')
			trans_mat_command(m, n, nr, mat);
		if (c == 'O')
			sort_mat_list(m, n, nr, mat);
		if (c == 'R')
			power_command(m, n, nr, mat);
		if (c == 'F')
			fold_command(&nr, mat, m, n);
		if (nr == size)
			extend_mat_list(&size, &nr, &m, &n, &mat);
		else if (2 * nr < size && nr != 0)
			retract_mat_list(&size, &nr, &m, &n, &mat);
		if (idf_char(c) == 0)
			error(-4);
	} while (c != 'Q');
	free_all(m, n, nr, mat);
	return 0;
}
