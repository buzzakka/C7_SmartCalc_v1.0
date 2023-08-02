#include "s21_smart_calc.h"

// инициализация
void init(stack_polish *stack) { stack->top = 0; }

// помещение элемента в стек
// Если sym = -1, то работа с числом
void push(stack_polish *stack, char sym, double num) {
  if (stack->top < NMAX) {
    if (sym != -1) {
      stack->char_elem[stack->top] = sym;
    } else {
      stack->double_elem[stack->top] = num;
    }
    stack->top++;
  }
}

// удаление элемента из стека
// Если sym == NULL, то работа с num
// Если num == NULL, то работа с sym
int pop(stack_polish *stack, char *sym, double *num) {
  int status = ERROR_FALSE;
  if (stack->top > 0) {
    stack->top--;
    if (num == NULL) {
      *sym = stack->char_elem[stack->top];
    } else {
      *num = stack->double_elem[stack->top];
    }
  } else {
    status = ERROR_TRUE;
  }
  return status;
}

// получение верхнего элемента стека без его удаления
// Если sym == NULL, то работа с num
// Если num == NULL, то работа с sym
void stack_top(stack_polish *stack, char *sym, double *num) {
  if (num == NULL) {
    *sym = stack->char_elem[stack->top - 1];
  } else {
    *num = stack->double_elem[stack->top - 1];
  }
}

// определение, пуст ли стек
int is_empty(stack_polish *stack) {
  int result = (stack->top == 0) ? 1 : 0;
  return result;
}