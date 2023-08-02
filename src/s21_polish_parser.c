#include "s21_smart_calc.h"

/*
    Добавления чего-либо в выходную строку
*/
void add_to_polish(char *polish_str, char sym) {
  char temp[2] = {'\0'};
  temp[0] = sym;
  strcat(polish_str, temp);
}

/*
    Добавления числа в выходную строку
*/
void add_num_to_polish(char *str, char *polish_str) {
  while (is_num(*str) || *str == '.') {
    add_to_polish(polish_str, *str);
    str++;
  }
  add_to_polish(polish_str, ' ');
}

/*
    Добавления знака в выходную строку/стэк
*/
void add_sign_to_polish(char str, char *polish_str, stack_polish *stack) {
  char sign_1 = 0;
  if (str == 'm') {
    sign_1 = '%';
  } else {
    sign_1 = str;
  }
  char sign_2 = 0;
  stack_top(stack, &sign_2, NULL);
  while ((get_priority(sign_1) <= get_priority(sign_2)) &&
         !(sign_1 == '^' && sign_2 == '^')) {
    pop(stack, &sign_2, NULL);
    add_to_polish(polish_str, sign_2);
    add_to_polish(polish_str, ' ');
    stack_top(stack, &sign_2, NULL);
  }
  push(stack, sign_1, 0);
}

/*
    Добавления скобок в выходную стэк
*/
int add_brace_to_polish(char str, char *polish_str, stack_polish *stack) {
  int status = ERROR_FALSE;
  if (str == '(') {
    push(stack, str, -1);
  } else {
    char elem = 0;
    stack_top(stack, &elem, NULL);
    while (elem != '(') {
      if (is_empty(stack)) {
        status = ERROR_TRUE;
        break;
      }
      pop(stack, &elem, NULL);
      add_to_polish(polish_str, elem);
      add_to_polish(polish_str, ' ');
      stack_top(stack, &elem, NULL);
    }
    pop(stack, &elem, NULL);
    stack_top(stack, &elem, NULL);
    if (is_polish_trgn(elem)) {
      pop(stack, &elem, NULL);
      add_to_polish(polish_str, elem);
      add_to_polish(polish_str, ' ');
    }
  }
  return status;
}

/*
    Добавление тригонометрии в польскую строку
    Значения:
    c - cos
    s - sin
    t - tan
    C - acos
    S - asin
    T - atan
    q - sqrt
    L - ln
    l - log
*/
void add_trgn_to_polish(int trgn_res, stack_polish *stack) {
  char sym = 0;
  switch (trgn_res) {
    case 1:
      sym = 'L';
      break;
    case 2:
      sym = 'c';
      break;
    case 3:
      sym = 's';
      break;
    case 4:
      sym = 't';
      break;
    case 5:
      sym = 'l';
      break;
    case 6:
      sym = 'C';
      break;
    case 7:
      sym = 'S';
      break;
    case 8:
      sym = 'T';
      break;
    case 9:
      sym = 'q';
      break;
    default:
      break;
  }
  push(stack, sym, 0);
}

/*
    Приоритет знаков
    ~ - унарный минус
    p - унарный плюс
    % - остаток деления
*/
int get_priority(char sym) {
  int priority = 0;
  switch (sym) {
    case '+':
    case '-':
      priority = 1;
      break;
    case '*':
    case '/':
    case '%':
      priority = 2;
      break;
    case '~':
    case 'p':
      priority = 3;
      break;
    case '^':
      priority = 4;
      break;
    default:
      break;
  }
  return priority;
}

/*
    Проверка на тригонометрию
*/
int is_polish_trgn(char trgn) {
  return (strchr("cstCSTqLl", trgn) != NULL && trgn != '\0');
}

void clean_polish(char *polish) {
  for (int i = 0; i < NMAX; i++) {
    polish[i] = '\0';
  }
}
