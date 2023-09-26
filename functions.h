// Copyright Razvan-Constantin Rus 312CAa 2022-2023

void swap_int(int *a, int *b);
void swap_long(long *a, long *b);
int valid_idx(long idx, long nr);
void cop_col(long m, long a, long b, int **mat_1, int **mat_2);
void swap_mat(long a, long b, int ***mat);
void cop_mat(long a, int **m, int **n);
int idf_char(char c);
int **mat_mult(long m, long n, long p, int **mat_1, int **mat_2);
int **mat_mult_ovrr(long m, long n, long p, int **mat_1, int **mat_2);
int **trans_mat(long m, long n, int **mat);
int **pow_mat(long n, int **mat, long pw);
int cut_mat(long *m, long *n, int ***mat);
