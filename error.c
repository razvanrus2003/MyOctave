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

void error(int a)
{
	if (a == 0)
		printf("Dinamic allocation failled\n");
	if (a == -1)
		printf("No matrix with the given index\n");
	if (a == -2)
		printf("Cannot perform matrix multiplication\n");
	if (a == -3)
		printf("Power should be positive\n");
	if (a == -4)
		printf("Unrecognized command\n");
}
