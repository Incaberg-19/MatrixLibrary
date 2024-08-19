#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_value = s21_is_matrix_bad(&A, 1, 0), check_eq_matrix = 0;

  if (return_value == OK) {
    matrix_t temp_result = {0};

    if (A != result) {
      return_value = s21_create_matrix(A->columns, A->rows, result);
    } else {
      return_value = s21_create_matrix(A->columns, A->rows, &temp_result);
      check_eq_matrix = 1;
    }

    if (return_value == OK) {
      if (check_eq_matrix == 1) {
        return_value = s21_matrix_trans_for_transpose(A, &temp_result);
        s21_remove_matrix(result);
        s21_copy_matrix(&temp_result, result, 1);
      } else {
        return_value = s21_matrix_trans_for_transpose(A, result);
      }
    }
    s21_remove_matrix(&temp_result);
  }

  return return_value;
}