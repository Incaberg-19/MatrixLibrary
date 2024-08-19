#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  matrix_t *temp[] = {A, B};
  int return_value = s21_is_matrix_bad(temp, 2, 1);

  if (return_value == OK) {
    return_value = SUCCESS;
    for (int i = 0; i < A->rows && return_value == SUCCESS; i++) {
      for (int j = 0; j < A->columns && return_value == SUCCESS; j++) {
        if (s21_check_accuracy(A->matrix[i][j], B->matrix[i][j], ACCURACY) ==
            1) {
          return_value = FAILURE;
        }
      }
    }
  } else {
    return_value = FAILURE;
  }

  return return_value;
}