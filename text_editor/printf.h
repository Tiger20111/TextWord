#ifndef TEXTEDITOR_PRINTF_H
#define TEXTEDITOR_PRINTF_H

#include "alllib.h"

int print_pages(struct stroki** Begin,int* numbers,int* wrap,int* tab,int num1,int num2,int kolSTR);
int print_range(struct stroki** Begin,int* numbers,int* wrap,int* tab,int *kolSTR);
int set_numbers(int* numbers);
int set_wrap(int* wrap);
int set_tabwidth(int* tab);

#endif

