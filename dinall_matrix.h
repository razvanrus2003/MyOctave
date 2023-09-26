// Copyright Razvan-Constantin Rus 312CAa 2022-2023

long *alloc_vec(long n);
int **load_mat(long m, long n);
void free_mat(long m, int **mat);
void free_all(long *m, long *n, long size, int ***mat);
void init_alloc(long size, int ****mat, long **m, long **n);
void my_exit(long *m, long *n, long nr, int ***mat);
