#include "s21_smart_calc.h"

int is_correct_string(char *str, char *polish) {
  if (str == NULL) return ERROR_TRUE;

  int status = ERROR_FALSE;
  char *temp_str = str;

  stack_polish stack = {0};
  init(&stack);

  if (*temp_str == '-' || *temp_str == '+') {
    char sign = (*temp_str == '-') ? '~' : 'p';
    add_sign_to_polish(sign, polish, &stack);
    temp_str++;
  }

  while (*temp_str != '=' && status != ERROR_TRUE) {
    int adder_length = 1;
    if (is_num(*temp_str)) {
      status = check_number(temp_str, &adder_length);
      if (status != ERROR_TRUE) add_num_to_polish(temp_str, polish);
    } else if (is_sign(temp_str)) {
      char sign = *temp_str;
      if (is_uno_sign(temp_str)) {
        sign = (sign == '-') ? '~' : 'p';
      }
      add_sign_to_polish(sign, polish, &stack);
      adder_length = (*temp_str == 'm') ? 3 : 1;
    } else if (is_brace(*temp_str)) {
      status = add_brace_to_polish(*temp_str, polish, &stack);
      if (*temp_str == '(' && *(temp_str + 1) == ')') status = ERROR_TRUE;
    } else if (is_func(temp_str)) {
      status = check_func(temp_str, &adder_length);
      if (status != ERROR_TRUE) add_trgn_to_polish(is_func(temp_str), &stack);
    } else if (*temp_str == 'x') {
      add_to_polish(polish, 'x');
      add_to_polish(polish, ' ');
    } else {
      status = ERROR_TRUE;
    }
    temp_str += adder_length;
  }

  if (status != ERROR_TRUE) {
    char sym = 0;
    stack_top(&stack, &sym, NULL);
    while (strchr("%~^p+-/*", sym) != NULL && sym != '\0') {
      pop(&stack, &sym, NULL);
      add_to_polish(polish, sym);
      if (!is_empty(&stack)) {
        add_to_polish(polish, ' ');
        stack_top(&stack, &sym, NULL);
      } else {
        break;
      }
    }
    if (is_brace(sym)) {
      status = ERROR_TRUE;
    }
  }
  if (status == ERROR_TRUE) {
    clean_polish(polish);
  }
  return status;
}

int check_number(char *str, int *length_of_num) {
  int status = ERROR_FALSE;
  *length_of_num = 0;
  while (is_num(*str)) {
    (*length_of_num)++;
    str++;
  }
  if (*str == '.') {
    str++;
    (*length_of_num)++;
    if (!is_num(*str)) {
      status = ERROR_TRUE;
    } else {
      while (is_num(*str)) {
        str++;
        (*length_of_num)++;
      }
    }
  }
  return status;
}

int check_func(char *str, int *length_of_func) {
  int status = ERROR_FALSE;

  *length_of_func = 0;
  if (is_func(str) == 1) *length_of_func = 2;
  if (is_func(str) >= 2 && is_func(str) <= 5) *length_of_func = 3;
  if (is_func(str) >= 6 && is_func(str) <= 9) *length_of_func = 4;

  if (*(str + *length_of_func) != '(') status = ERROR_TRUE;

  return status;
}

int is_uno_sign(char *str) {
  int result = 0;
  if ((*str == '-' || *str == '+') && *(str - 1) == '(') {
    result = 1;
  }
  return result;
}

int is_num(char sym) { return (sym >= '0' && sym <= '9'); }

int is_brace(char sym) { return (sym == '(' || sym == ')'); }

int is_sign(char *sym) {
  return (strchr("+-*/^", *sym) != NULL || strncmp(sym, "mod", 3) == 0);
}

/*
    Проверка что это функция
*/
int is_func(char *str) {
  int result = 0;
  if (strncmp(str, "ln", 2) == 0) {
    result = 1;
  } else if (strncmp(str, "cos", 3) == 0) {
    result = 2;
  } else if (strncmp(str, "sin", 3) == 0) {
    result = 3;
  } else if (strncmp(str, "tan", 3) == 0) {
    result = 4;
  } else if (strncmp(str, "log", 3) == 0) {
    result = 5;
  } else if (strncmp(str, "acos", 4) == 0) {
    result = 6;
  } else if (strncmp(str, "asin", 4) == 0) {
    result = 7;
  } else if (strncmp(str, "atan", 4) == 0) {
    result = 8;
  } else if (strncmp(str, "sqrt", 4) == 0) {
    result = 9;
  }
  return result;
}