#include "../s21_matrix.h"
int s21_sum_sub(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
  matrix_t *temp[] = {A, B};
  int return_value = s21_is_matrix_bad(temp, 2, 1);
  if (return_value == OK) {
    if (result != A && result != B) {
      return_value = s21_create_matrix(A->rows, A->columns, result);
    }
    if (return_value == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + sign * B->matrix[i][j];
        }
      }
    }
  }

  return return_value;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sum_sub(A, B, result, 1);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sum_sub(A, B, result, -1);
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  matrix_t *temp[] = {A, B};
  int return_value = s21_is_matrix_bad(temp, 2, 3);

  if (return_value == OK) {
    return_value = s21_create_matrix(A->rows, B->columns, result);
    if (return_value == OK) {
      return_value = matrix_trans_for_mult_matrix(A, B, result);
    }
  }

  return return_value;
}

int matrix_trans_for_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_value = OK;

  matrix_t copy_A = {0};
  matrix_t copy_B = {0};

  return_value = s21_copy_matrix(A, &copy_A, 1);
  if (return_value == OK) {
    return_value = s21_copy_matrix(B, &copy_B, 1);
  }

  for (int i = 0; i < A->rows && return_value == OK; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < B->rows; k++) {
        result->matrix[i][j] += copy_A.matrix[i][k] * copy_B.matrix[k][j];
      }
    }
  }

  s21_remove_matrix(&copy_A);
  s21_remove_matrix(&copy_B);

  return return_value;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int return_value = s21_is_matrix_bad(&A, 1, 0);

  if (return_value == OK) {
    if (A != result) {
      return_value = s21_create_matrix(A->rows, A->columns, result);
    }

    if (return_value == OK) {
      matrix_t copy = {0};
      return_value = s21_copy_matrix(A, &copy, 1);

      for (int i = 0; i < A->rows && return_value == OK; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = number * copy.matrix[i][j];
        }
      }

      s21_remove_matrix(&copy);
    }
  }

  return return_value;
}