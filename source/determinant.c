#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int return_value = s21_is_matrix_bad(&A, 1, 2);

  if (return_value == OK) {
    matrix_t copy = {0};
    return_value = s21_copy_matrix(A, &copy, 1);

    if (return_value == OK) {
      int swap_count = 0;
      *result = 0;
      for (int i = 0; i < copy.rows; i++) {
        s21_matrix_trans_for_det(&copy, &swap_count, &i);
      }

      if (swap_count >= 0) {
        *result = 1.0;
        for (int i = 0; i < copy.rows; i++) {
          *result *= copy.matrix[i][i];
        }

        // Меняем знак результата в зависимости от количества перестановок
        if (swap_count & 1) *result *= -1;
      }
    }
    s21_remove_matrix(&copy);
  }

  return return_value;
}