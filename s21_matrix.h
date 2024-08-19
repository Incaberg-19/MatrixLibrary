#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define SUCCESS 1
#define FAILURE 0

#define ACCURACY 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// ОСНОВНЫЕ ФУНКЦИИ
int s21_calc_complements(matrix_t *A, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
int matrix_trans_for_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_matrix_trans_for_inverse(matrix_t *A, matrix_t *result, double det);
int s21_simple_calccomp_inverse(matrix_t *A, matrix_t *result, int key);
int s21_check_parameters_for_create(int rows, int colums, matrix_t *A);
int s21_sum_sub(matrix_t *A, matrix_t *B, matrix_t *result, int sign);
int s21_matrix_trans_for_det(matrix_t *A, int *swap_count, int *i);
int s21_matrix_trans_for_transpose(matrix_t *A, matrix_t *result);
int s21_copy_matrix(matrix_t *A, matrix_t *result, int key);
int s21_check_accuracy(double a, double b, double epsilon);
void s21_swap_rows(matrix_t *matrix, int row1, int row2);
int s21_is_matrix_bad(matrix_t *A[], int count, int key);
int s21_other_options(matrix_t *A[], int count, int key);
void s21_do_triangular_matrix_form(matrix_t *A, int i);
int s21_free_when_allocation_fail(matrix_t *A, int i);
int s21_matrix_trans_for_calc_comp(matrix_t *A, matrix_t *temp, int k,
                                   matrix_t *result);
long double s21_fabs(double x);

#endif