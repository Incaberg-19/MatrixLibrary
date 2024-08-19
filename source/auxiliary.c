#include <stdlib.h>

#include "../s21_matrix.h"
int s21_copy_matrix(matrix_t *A, matrix_t *result, int key) {
  // ключ позволяет решать пользователю когда нужно выделять память для result
  int return_value = OK;

  if (key == 1) {
    return_value = s21_create_matrix(A->rows, A->columns, result);
  }

  for (int i = 0; i < A->rows && return_value == OK; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j];
    }
  }

  return return_value;
}

int s21_matrix_trans_for_transpose(matrix_t *A, matrix_t *result) {
  matrix_t copy = {0};
  int return_value = s21_copy_matrix(A, &copy, 1);
  if (return_value == OK) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = copy.matrix[j][i];
      }
    }
  }
  s21_remove_matrix(&copy);
  return return_value;
}

void s21_swap_rows(matrix_t *matrix, int row1, int row2) {
  for (int j = 0; j < matrix->columns; j++) {
    double temp = matrix->matrix[row1][j];
    matrix->matrix[row1][j] = matrix->matrix[row2][j];
    matrix->matrix[row2][j] = temp;
  }
}

void s21_do_triangular_matrix_form(matrix_t *A, int i) {
  double ratio = 1.0;
  for (int j = i + 1; j < A->rows; j++) {
    if (A->matrix[i][i] != 0) {
      ratio = A->matrix[j][i] / A->matrix[i][i];
      for (int k = i; k < A->columns; k++) {
        A->matrix[j][k] -= ratio * A->matrix[i][k];
      }
    }
  }
}

int s21_matrix_trans_for_det(matrix_t *A, int *swap_count, int *i) {
  int foundNonZero = 0, return_value = OK;
  if (return_value == OK) {
    for (int j = *i + 1; j < A->rows && !foundNonZero; j++) {
      if (A->matrix[j][*i] != 0) {
        // Обмен строк, если найден ненулевой элемент ниже
        s21_swap_rows(A, *i, j);
        *swap_count = *swap_count + 1;
        foundNonZero = 1;
      }
    }

    if (A->matrix[*i][*i] == 0 && !foundNonZero) {
      *i = A->rows;
      *swap_count = -1;
    } else {
      s21_do_triangular_matrix_form(A, *i);
    }
  }
  return return_value;
}

int s21_other_options(matrix_t *A[], int count, int key) {
  // key=1 - проверка на сходные размеры матриц
  // key=2 - проверка на квадратную матрицу
  // key=3 - количество столбцов первой матрицы должно быть равно количеству
  // строк второй матрицы
  int return_value = OK;

  if (key == 3 && (A[0]->columns != A[1]->rows)) {
    return_value = CALCULATION_ERROR;
  }

  for (int i = 0; i < count && return_value == OK; i++) {
    if (key == 1 &&
        (A[i]->rows != A[0]->rows || A[i]->columns != A[0]->columns)) {
      return_value = CALCULATION_ERROR;
    } else if (key == 2 && (A[i]->rows != A[i]->columns)) {
      return_value = CALCULATION_ERROR;
    }
  }

  return return_value;
}

int s21_matrix_trans_for_inverse(matrix_t *A, matrix_t *result, double det) {
  matrix_t temp_result = {0};
  int return_value = s21_calc_complements(A, &temp_result);

  if (return_value == OK) {
    return_value = s21_transpose(&temp_result, &temp_result);
    if (return_value == OK) {
      return_value = s21_mult_number(&temp_result, 1 / det, &temp_result);
    }
  }

  if (return_value == OK) {
    return_value = s21_copy_matrix(&temp_result, result, 0);
  }

  s21_remove_matrix(&temp_result);

  return return_value;
}

int s21_is_matrix_bad(matrix_t *A[], int count, int key) {
  int return_value = OK;
  for (int i = 0; i < count && return_value == OK; i++) {
    if (A[i] != NULL) {
      if (A[i]->rows <= 0 || A[i]->columns <= 0) {
        return_value = INCORRECT_MATRIX;
      }
    } else {
      return_value = INCORRECT_MATRIX;
    }
  }
  if (return_value == OK && key != 0) {
    return_value = s21_other_options(A, count, key);
  }
  return return_value;
}

int s21_simple_calccomp_inverse(matrix_t *A, matrix_t *result, int key) {
  // key=1 - inverse
  // key=0 calc_comp
  int return_value = OK;

  if (A->rows == A->columns && A->rows == 1) {
    if (A != result) {
      return_value = s21_create_matrix(A->rows, A->columns, result);
    }
    if (return_value == OK) {
      if (key == 0) {
        result->matrix[0][0] = 1;
      }
      if (key == 1) {
        result->matrix[0][0] = 1 / A->matrix[0][0];
      }
      return_value = -1;  // чтобы отследить что отработала эта ф-ия
    }
  }

  return return_value;
}

long double s21_fabs(double x) { return (x < 0) ? x * (-1) : x; }

int s21_check_accuracy(double a, double b, double epsilon) {
  double diff = s21_fabs(a - b);
  return (diff > epsilon);
}

int s21_free_when_allocation_fail(matrix_t *A, int i) {
  int return_value = CALCULATION_ERROR;

  for (int j = 0; j < i; j++) {
    free(A->matrix[j]);
  }
  free(A->matrix);

  A->matrix = NULL;

  return return_value;
}
