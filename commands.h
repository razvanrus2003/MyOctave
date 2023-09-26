// Copyright Razvan-Constantin Rus 312CAa 2022-2023

void print_dimensions(long nr, long *m, long *n);
void sort_mat_list(long *m, long *n, long nr, int ***mat);
void cut_mat_command(long *m, long *n, long nr, int ***mat);
void fold_command(long *nr, int ***mat, long *m, long *n);
void power_command(long *m, long *n, long nr, int ***mat);
void load_command(long *m, long *n, long *nr, int ***mat);
void print_mat_command(long *m, long *n, long nr, int ***mat);
void trans_mat_command(long *m, long *n, long nr, int ***mat);
void multiply_command(long *m, long *n, long *nr, int ***mat);
void strassen_command(long *m, long *n, long *nr, int ***mat);
void extend_mat_list(long *size, long *nr, long **m, long **n, int ****mat);
void retract_mat_list(long *size, long *nr, long **m, long **n, int ****mat);
