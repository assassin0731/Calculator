#include <check.h>

#include "CalcFiles/calc.h"

START_TEST(test_1) {
  char *string = "sin(10)";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = sin(10);
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_2) {
  char *string = "sin(10)+1-2/3+tg(100)";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = sin(10) + 1 - 2. / 3 + tan(100);
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_3) {
  char *string = "abs(cos(10)-12^3+25)+asin(0.5)+10%3";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = fabs(cos(10) - pow(12, 3) + 25) + asin(0.5) + 10 % 3;
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_4) {
  char *string = "+10-20";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Ошибка в записи";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_5) {
  char *string = "(123-10)/sin(0)";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Деление на 0";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_6) {
  char *string = "sin(123)-.123+12";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Ошибка в записи";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_7) {
  char *string = "512-asin(0.12.1)";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Ошибка в записи";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_8) {
  char *string = "512-asin(0.121)+25-100*(10/2))";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Неправильно расставлены скобки";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_9) {
  char string[255] = "sqrt(-1)";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Отрицательный корень";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_10) {
  char string[255] = "1+3/2+ln(-20)";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Несуществующий логарифм";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_11) {
  char string[255] = "1+3/2+log(-20)";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Несуществующий логарифм";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_12) {
  char string[255] = "asin(0.2)+acos(-0.1)/ln(10)+tg(1.2^3+log(25))";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = asin(0.2) + acos(-0.1) / log(10) + tan(pow(1.2, 3) + log10(25));
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_13) {
  char string[255] = "x+2*x-3/2";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result[10000];
  double startX = -10;
  double x = 2. * 10. / N;
  for (int i = 0; i < 10000; i++) {
    real_result[i] = startX + 2 * startX - 3. / 2;
    startX += x;
  }
  calculation(string, result, NAN, 10, mas_y);
  for (int i = 0; i < 10000; i++) {
    ck_assert_double_eq_tol(mas_y[i], real_result[i], eps);
  }
}
END_TEST

START_TEST(test_14) {
  char string[255] = "1+3/2+log(20)+999999912345699999";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Слишком большое число";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_15) {
  char string[255] = "(25*12-(12/3-(12*3))";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Неправильно расставлены скобки";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_16) {
  char string[255] = "1+3/2+log(20)+900719925474199";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Слишком большое число";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_17) {
  char string[255] = "1+3/2+log(20)+900719925474099.123";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Слишком большое число";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_18) {
  char string[255] = "sin(x)/cos(x)";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = sin(0.3) / cos(0.3);
  calculation(string, result, 0.3, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_19) {
  char string[255] = "sqrt(125*3/2^1.2)";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = sqrt(125 * 3 / pow(2, 1.2));
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_20) {
  char string[255] = "atan(sqrt(ln(asin(0.5)+5)))";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = atan(sqrt(log(asin(0.5) + 5)));
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_21) {
  char *string = "(123-10)%sin(0)";
  char result[255] = {'\0'};
  double mas_y[10000];
  char *real_result = "Деление на 0";
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_pstr_eq(result, real_result);
}
END_TEST

START_TEST(test_22) {
  char string[255] = "sqrt(abs(20-sin(25)+10*2-asin(0.1)))";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = sqrt(fabs(20 - sin(25) + 10 * 2 - asin(0.1)));
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_23) {
  char string[255] = "sin(cos(sin(cos(sqrt(abs(1.4+12.3%2.1))))))";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = sin(cos(sin(cos(sqrt(fabs(1.4 + fmod(12.3, 2.1)))))));
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_24) {
  char string[255] = "10/9/8/7/6/5/4+12*2-3*tg(125+cos(123))";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = 180.8743346;
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

START_TEST(test_25) {
  char string[255] = "12351*2+2153443-345324+2342+3452-34523*12";
  char result[255] = {'\0'};
  double mas_y[10000];
  double real_result = 0;
  real_result = 12351 * 2 + 2153443 - 345324 + 2342 + 3452 - 34523 * 12;
  calculation(string, result, NAN, 1, mas_y);
  ck_assert_double_eq_tol(mas_y[0], real_result, eps);
}
END_TEST

int main() {
  Suite *s1 = suite_create("s21_calc: ");
  TCase *tc1_1 = tcase_create("s21_calc: ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_1);
  tcase_add_test(tc1_1, test_2);
  tcase_add_test(tc1_1, test_3);
  tcase_add_test(tc1_1, test_4);
  tcase_add_test(tc1_1, test_5);
  tcase_add_test(tc1_1, test_6);
  tcase_add_test(tc1_1, test_7);
  tcase_add_test(tc1_1, test_8);
  tcase_add_test(tc1_1, test_9);
  tcase_add_test(tc1_1, test_10);
  tcase_add_test(tc1_1, test_11);
  tcase_add_test(tc1_1, test_12);
  tcase_add_test(tc1_1, test_13);
  tcase_add_test(tc1_1, test_14);
  tcase_add_test(tc1_1, test_15);
  tcase_add_test(tc1_1, test_16);
  tcase_add_test(tc1_1, test_17);
  tcase_add_test(tc1_1, test_18);
  tcase_add_test(tc1_1, test_19);
  tcase_add_test(tc1_1, test_20);
  tcase_add_test(tc1_1, test_21);
  tcase_add_test(tc1_1, test_22);
  tcase_add_test(tc1_1, test_23);
  tcase_add_test(tc1_1, test_24);
  tcase_add_test(tc1_1, test_25);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
