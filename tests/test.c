#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

void set(double *array, matrix_t *A) {
  int k = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = array[k++];
    }
  }
}

START_TEST(test_s21_create_matrix) {
  matrix_t s21_matrix;

  ck_assert_int_eq(s21_create_matrix(5, 5, &s21_matrix), 0);
  s21_remove_matrix(&s21_matrix);

  ck_assert_int_eq(s21_create_matrix(0, 0, &s21_matrix), 1);
  ck_assert_int_eq(s21_create_matrix(-1, 10, &s21_matrix), 1);
  ck_assert_int_eq(s21_create_matrix(1, -10, &s21_matrix), 1);
  ck_assert_int_eq(s21_create_matrix(5, 5, NULL), 1);
  s21_create_matrix(5, 5, &s21_matrix);
  s21_remove_matrix(NULL);
  s21_remove_matrix(&s21_matrix);
}
END_TEST

START_TEST(test_s21_arithmetic) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &B), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(NULL, &A, &B), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &B), INCORRECT_MATRIX);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &B), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(NULL, &A, &B), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &B), INCORRECT_MATRIX);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(5, 5, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), CALCULATION_ERROR);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double B_nums[6] = {2, 3, 4, 5, 6, 7};
  double result_nums[6] = {3, 5, 7, 9, 11, 13};
  double nulli[6] = {0, 0, 0, 0, 0, 0};
  set(nulli, &B);

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &A, &A), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &C);
  set(A_nums, &A);
  set(B_nums, &B);
  set(result_nums, &C);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &D), 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);

  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
  for (int i = 0; i < 6; i++) {
    result_nums[i] = -1;
  }
  s21_create_matrix(3, 2, &C);
  set(result_nums, &C);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &D), 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(s21_eq_matrix(&C, &A), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(s21_mult_number(NULL, 10.0, &A), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_number(&A, 10.0, NULL), INCORRECT_MATRIX);

  s21_create_matrix(10, 10, &A);

  ck_assert_int_eq(s21_mult_number(&A, 10.0, &C), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, &C), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);

  double number = 3901.904;

  double H_nums[9] = {121239.122013, 2401.12392,   -348901.2, 2389014,
                      912039.12389,  129034.23400, 0,         1203,
                      9000000.123};
  double nums[9] = {473063415.139012752,
                    9368955.02794368,
                    -1361378987.8848,
                    9321703282.656,
                    3558689105.66288656,
                    503479193.781536,
                    0,
                    4693990.512,
                    35117136479.934192};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  set(H_nums, &A);
  set(nums, &B);
  int res = s21_mult_number(&A, number, &C);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(s21_mult_matrix(NULL, &A, &A), 1);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &A), 1);
  ck_assert_int_eq(s21_mult_matrix(&A, &A, NULL), 1);

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  double Q_nums[6] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2};
  double S_nums[6] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0};
  double result_num[9] = {92.4, 117.6, 205.8, 268.8};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &C);
  set(Q_nums, &A);
  set(S_nums, &B);
  set(result_num, &C);

  res = s21_mult_matrix(&A, &B, &D);

  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), 1);
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  double A_nums[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double result_nums[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 16;
  res = s21_calc_complements(&A, &A);
  s21_create_matrix(1, 1, &B);
  B.matrix[0][0] = 1;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  double H_nums[9] = {5, -1, 1, 2, 3, 4, 1, 0, 3};
  double Q_nums[9] = {9, -2, -3, 3, 14, -1, -7, -18, 17};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  set(H_nums, &A);
  set(Q_nums, &B);
  ck_assert_int_eq(s21_calc_complements(&A, &A), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  ck_assert_int_eq(s21_transpose(NULL, &A), 1);
  ck_assert_int_eq(s21_transpose(&A, NULL), 1);
  ck_assert_int_eq(s21_transpose(&A, &A), 1);
  s21_create_matrix(10, 10, &A);
  ck_assert_int_eq(s21_transpose(&A, &A), 0);
  s21_remove_matrix(&A);

  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double result_nums[6] = {1, 4, 2, 5, 3, 6};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_s21_determinant) {
  matrix_t A = {0};
  double determinant = 2.0;
  ck_assert_int_eq(s21_determinant(&A, &determinant), 1);
  ck_assert_int_eq(s21_determinant(&A, NULL), 1);
  ck_assert_int_eq(s21_determinant(NULL, &determinant), 1);

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 0.0;
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, 0.0, ACCURACY);
  s21_remove_matrix(&A);

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1.0;
  ck_assert_uint_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq_tol(determinant, 1.0, ACCURACY);
  s21_remove_matrix(&A);

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = -213123.464566456;
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -213123.464566456, ACCURACY);
  s21_remove_matrix(&A);

  double arr[4] = {0, 0, 0, 0};
  s21_create_matrix(2, 2, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, 0., ACCURACY);
  s21_remove_matrix(&A);

  double arra[16] = {4.,  4., 4.,  4.,  5., 6.,  7.,  8.,
                     10., 2., 12., 13., 1., 16., 17., 4.};

  s21_create_matrix(4, 5, &A);
  ck_assert_int_eq(s21_determinant(&A, &determinant), 2);
  s21_remove_matrix(&A);

  s21_create_matrix(4, 4, &A);
  set(arra, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -1512., ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  int res = 0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &A), 1);
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), 1);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &A), 1);
  s21_create_matrix(10, 10, &A);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &A), 1);
  ck_assert_int_eq(s21_inverse_matrix(&A, &A), 2);
  s21_remove_matrix(&A);

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &C);
  A.matrix[0][0] = 42.12849;
  C.matrix[0][0] = 1. / 42.12849;
  res = s21_inverse_matrix(&A, &B);
  ck_assert_double_eq(s21_eq_matrix(&B, &C), 1);

  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  double A_nums[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double result_nums[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  res = s21_inverse_matrix(&A, &A);
  ck_assert_double_eq(s21_eq_matrix(&A, &C), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  res = s21_inverse_matrix(&A, &B);
  ck_assert_double_eq(s21_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_NULLS) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_eq_matrix(&A, &A), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), 0);
  ck_assert_int_eq(s21_eq_matrix(NULL, &A), 0);
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), 0);

  ck_assert_int_eq(s21_calc_complements(&A, &A), 1);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), 1);
  ck_assert_int_eq(s21_calc_complements(NULL, &A), 1);
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), 1);

  ck_assert_int_eq(s21_create_matrix(5, 4, NULL), 1);

  double det = 0;
  ck_assert_int_eq(s21_determinant(NULL, &det), 1);

  ck_assert_int_eq(s21_inverse_matrix(&A, &A), 1);
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), 1);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &A), 1);
  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), 1);

  ck_assert_int_eq(s21_sum_matrix(&A, &A, &A), 1);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &A), 1);
  ck_assert_int_eq(s21_sum_matrix(NULL, &A, NULL), 1);
  ck_assert_int_eq(s21_sum_matrix(&A, &A, NULL), 1);

  ck_assert_int_eq(s21_sub_matrix(&A, &A, &A), 1);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &A), 1);
  ck_assert_int_eq(s21_sub_matrix(NULL, &A, NULL), 1);
  ck_assert_int_eq(s21_sub_matrix(&A, &A, NULL), 1);

  ck_assert_int_eq(s21_transpose(&A, &A), 1);
  ck_assert_int_eq(s21_transpose(&A, NULL), 1);
  ck_assert_int_eq(s21_transpose(NULL, &A), 1);
  ck_assert_int_eq(s21_transpose(NULL, NULL), 1);

  ck_assert_int_eq(s21_mult_number(&A, det, &A), 1);
  ck_assert_int_eq(s21_mult_number(NULL, det, &A), 1);
  ck_assert_int_eq(s21_mult_number(&A, det, NULL), 1);

  ck_assert_int_eq(s21_mult_matrix(&A, &A, &A), 1);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &A), 1);
  ck_assert_int_eq(s21_mult_matrix(NULL, &A, NULL), 1);
  ck_assert_int_eq(s21_mult_matrix(&A, &A, NULL), 1);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  matrix_t s21_matrixA = {0};
  matrix_t s21_matrixB = {0};

  s21_create_matrix(5, 5, &s21_matrixA);
  s21_create_matrix(5, 5, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 1);

  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(2, 5, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 0);

  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(5, 1, &s21_matrixA);
  s21_create_matrix(5, 2, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 0);

  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(5, 5, &s21_matrixA);
  s21_create_matrix(5, 5, &s21_matrixB);
  s21_matrixA.matrix[0][0] = 10;
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 0);

  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(5, 5, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(NULL, &s21_matrixB), 0);

  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(5, 5, &s21_matrixA);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, NULL), 0);

  s21_remove_matrix(&s21_matrixA);

  s21_create_matrix(1, 1, &s21_matrixA);
  s21_create_matrix(1, 1, &s21_matrixB);
  s21_matrixA.matrix[0][0] = 10;
  s21_matrixB.matrix[0][0] = 10;
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 1);
  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(3, 2, &s21_matrixA);
  s21_create_matrix(3, 2, &s21_matrixB);
  double ar1[] = {1, 2, 3, 4, 5, 6};
  set(ar1, &s21_matrixA);
  set(ar1, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 1);
  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);
}
END_TEST

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  srunner_set_fork_status(runner, CK_NOFORK);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

Suite *s21_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_create_matrix);
  tcase_add_test(tc_core, test_s21_arithmetic);
  tcase_add_test(tc_core, test_s21_transpose);
  tcase_add_test(tc_core, test_s21_determinant);
  tcase_add_test(tc_core, test_s21_inverse_matrix);
  tcase_add_test(tc_core, test_s21_calc_complements);
  tcase_add_test(tc_core, test_s21_eq_matrix);
  tcase_add_test(tc_core, test_NULLS);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_falied = 0;

  case_test(s21_matrix_suite(), &no_falied);
  return !no_falied ? 0 : 1;
}