#include "s21_smart_calc.h"

int credit_calc(double total_sum, int time, double procent_rate, int type,
                double *month_pay, double *overpay, double *total_pay) {
  int status = ERROR_FALSE;
  if (total_sum < 0 || time < 1 || procent_rate < 0 || procent_rate >= 100 ||
      type < 1 || type > 2 || procent_rate < 0.01) {
    status = ERROR_TRUE;
  } else {
    if (type == 1) {
      double i = procent_rate / 100 / 12;
      month_pay[0] = total_sum * (i + (i / (pow(1 + i, time) - 1)));
      *total_pay = time * month_pay[0];
      *overpay = *total_pay - total_sum;
    }
    if (type == 2) {
      *total_pay = 0;
      for (int i = 1; i <= time; i++) {
        month_pay[i - 1] =
            (total_sum) / time + (total_sum - (total_sum / time) * (i - 1)) *
                                     ((procent_rate / 100) / 12);
        *total_pay += month_pay[i - 1];
      }
      *overpay = *total_pay - total_sum;
    }
  }
  return status;
}