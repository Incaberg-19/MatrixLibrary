#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int return_value = s21_is_matrix_bad(&A, 1, 2);

  if (return_value == OK) {
    return_value = s21_simple_calccomp_inverse(A, result, 1);
  }

  if (return_value == OK) {
    if (A != result) {
      return_value = s21_create_matrix(A->rows, A->columns, result);
    }
    if (return_value == OK) {
      double det = 0;
      return_value = s21_determinant(A, &det);
      if (det == 0 && return_value == OK) {
        return_value = CALCULATION_ERROR;
      }
      if (return_value == OK) {
        return_value = s21_matrix_trans_for_inverse(A, result, det);
      }
    }
  }

  if (return_value == -1) {
    return_value = OK;
  }

  return return_value;
}