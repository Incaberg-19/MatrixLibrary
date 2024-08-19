#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int return_value = s21_is_matrix_bad(&A, 1, 0);

  if (return_value == OK) {
    return_value = s21_simple_calccomp_inverse(A, result, 0);
  }

  if (return_value == OK) {
    if (A != result) {
      return_value = s21_create_matrix(A->rows, A->columns, result);
    }
    if (return_value == OK) {
      matrix_t temp = {0};
      return_value = s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
      if (return_value == OK) {
        matrix_t res_temp = {0};
        return_value =
            s21_create_matrix(result->rows, result->columns, &res_temp);

        for (int k = 0; k < A->rows && return_value == OK; k++) {
          return_value = s21_matrix_trans_for_calc_comp(A, &temp, k, &res_temp);
        }

        if (return_value == OK) {
          return_value = s21_copy_matrix(&res_temp, result, 0);
        }

        s21_remove_matrix(&res_temp);
      }
      s21_remove_matrix(&temp);
    }
  }

  if (return_value == -1) {
    return_value = OK;
  }

  return return_value;
}

int s21_matrix_trans_for_calc_comp(matrix_t *A, matrix_t *temp, int k,
                                   matrix_t *result) {
  int return_value = OK;

  for (int l = 0; l < A->columns && return_value == OK; l++) {
    int c = 0, h = 0;
    for (int i = 0; i < A->rows; i++) {
      if (k == i) continue;

      for (int j = 0; j < A->columns; j++) {
        if (l == j) continue;
        temp->matrix[c][h] = A->matrix[i][j];
        h++;
      }
      c++;
      h = 0;
    }

    return_value = s21_determinant(temp, &result->matrix[k][l]);
    if (return_value == OK) {
      result->matrix[k][l] = ((k + l) & 1 ? -1 : 1) * result->matrix[k][l];
    }
  }

  return return_value;
}