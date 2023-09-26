// Copyright Razvan-Constantin Rus 312CAa 2022-2023

int **strassen(long n, int **mat_1, int **mat_2);
void squad_free(long n, int **a, int **b, int **c, int **d);
int **sum_mat(long n, int **a, int **b);
int **sum_mat_ovrr(long n, int **a, int **b);
int **dif_mat(long n, int **a, int **b);
int **dif_mat_ovrr(long n, int **a, int **b);
int **matrix_divider(int **mat, long n, int c);
int **m_alloc_1(long n, int **a, int **d, int **x, int **t);
int **m_alloc_2(long n, int **c, int **d, int **x);
int **m_alloc_3(long n, int **a, int **y, int **t);
int **m_alloc_4(long n, int **d, int **z, int **x);
int **m_alloc_5(long n, int **a, int **b, int **t);
int **m_alloc_6(long n, int **c, int **a, int **x, int **y);
int **m_alloc_7(long n, int **b, int **d, int **z, int **t);
int **matrix_constructor(long n, int **a, int **b, int **c, int **d);
int general_mat_div(long n, int ***a, int ***b, int ***c, int ***d, int **mat);
