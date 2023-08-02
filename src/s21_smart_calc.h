#ifndef SRC_SMART_CALC_H_
#define SRC_SMART_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FALSE 0
#define ERROR_TRUE 1

#define NMAX 255

typedef struct stack {
  char char_elem[NMAX];
  double double_elem[NMAX];
  int top;
} stack_polish;

int is_correct_string(char *str, char *polish);

int check_number(char *str, int *length_of_num);
int check_func(char *str, int *length_of_func);

int is_num(char sym);
int is_sign(char *sym);
int is_uno_sign(char *str);
int is_brace(char sym);
int is_func(char *str);

void init(stack_polish *stack);
void push(stack_polish *stack, char sym, double num);
int pop(stack_polish *stack, char *sym, double *num);
void stack_top(stack_polish *stack, char *sym, double *num);
int is_empty(stack_polish *stack);

void add_to_polish(char *polish_str, char sym);
void add_num_to_polish(char *str, char *polish_str);
void add_sign_to_polish(char str, char *polish_str, stack_polish *stack);
void add_trgn_to_polish(int trgn_res, stack_polish *stack);
int add_brace_to_polish(char str, char *polish_str, stack_polish *stack);
int is_polish_trgn(char trgn);
int get_priority(char sym);
void clean_polish(char *polish);

void make_polish_copy(char *original, char *copy);

int calc(char *polish, double *result, double x);
int smart_calc(char *str, double *result, double x);

int credit_calc(double total_sum, int time, double procent_rate, int type,
                double *month_pay, double *overpay, double *total_pay);

#endif
