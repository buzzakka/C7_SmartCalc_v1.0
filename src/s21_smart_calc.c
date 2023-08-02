#include "s21_smart_calc.h"

int calc(char *polish, double *result, double x) {
  int status = ERROR_FALSE;
  char polish_copy[255] = {0};
  strcpy(polish_copy, polish);

  char *lexem = 0;
  stack_polish stack = {0};
  init(&stack);
  lexem = strtok(polish_copy, " ");

  while (lexem != NULL && status != ERROR_TRUE) {
    if (is_num(*lexem)) {
      double num = atof(lexem);
      push(&stack, -1, num);
    } else if (*lexem == 'x') {
      push(&stack, -1, x);
    } else {
      if (*lexem == '~' || *lexem == 'p' || is_polish_trgn(*lexem)) {
        if (is_empty(&stack)) {
          status = ERROR_TRUE;
        } else {
          double num_1 = 0;
          pop(&stack, NULL, &num_1);
          switch (*lexem) {
            case '~':
              num_1 = -num_1;
              break;
            case 'p':
              num_1 = +num_1;
              break;
            case 's':
              num_1 = sin(num_1);
              break;
            case 'c':
              num_1 = cos(num_1);
              break;
            case 't':
              num_1 = tan(num_1);
              break;
            case 'S':
              num_1 = asin(num_1);
              break;
            case 'C':
              num_1 = acos(num_1);
              break;
            case 'T':
              num_1 = atan(num_1);
              break;
            case 'L':
              num_1 = log(num_1);
              break;
            case 'l':
              num_1 = log10(num_1);
              break;
            case 'q':
              num_1 = sqrt(num_1);
              break;
            default:
              break;
          }
          push(&stack, -1, num_1);
        }
      } else {
        if (stack.top <= 1) {
          status = ERROR_TRUE;
        } else {
          double num_1 = 0;
          double num_2 = 0;
          pop(&stack, NULL, &num_1);
          pop(&stack, NULL, &num_2);
          switch (*lexem) {
            case '+':
              num_2 += num_1;
              break;
            case '-':
              num_2 -= num_1;
              break;
            case '*':
              num_2 *= num_1;
              break;
            case '/':
              num_2 /= num_1;
              break;
            case '%':
              num_2 = fmod(num_2, num_1);
              break;
            case '^':
              num_2 = pow(num_2, num_1);
              break;

            default:
              break;
          }
          push(&stack, -1, num_2);
        }
      }
    }
    lexem = strtok(NULL, " ");
  }
  if (stack.top != 1) status = ERROR_TRUE;
  if (status != ERROR_TRUE) pop(&stack, NULL, result);
  return status;
}

int smart_calc(char *str, double *result, double x) {
  char polish[255] = {0};
  int status = is_correct_string(str, polish);
  if (strchr(polish, 'x') != NULL) {
    char *temp = polish;
    status = calc(temp, result, x);
  } else {
    if (status == ERROR_FALSE) {
      char *temp = polish;
      status = calc(temp, result, 0);
    }
  }
  return status;
}