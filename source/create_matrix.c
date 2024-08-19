#include <stdlib.h>

#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int return_value = s21_check_parameters_for_create(rows, columns, result);
  if (return_value == OK) {
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {  // Ошибка выделения памяти
      return_value = CALCULATION_ERROR;
    }
    for (int i = 0; i < rows && return_value == OK; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        return_value = s21_free_when_allocation_fail(result, i);
        // Если не удалось выделить память для одной из строк, освобождаем уже
        // выделенную память
      }
    }
    if (return_value == OK) {
      result->rows = rows;
      result->columns = columns;
    }
  }

  return return_value;
}

int s21_check_parameters_for_create(int rows, int colums, matrix_t *A) {
  int return_value = OK;

  if (rows <= 0 || colums <= 0 || A == NULL) {
    return_value = INCORRECT_MATRIX;
  }
  return return_value;
}