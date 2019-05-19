#ifndef TEXTEDITOR_INSERT_SYMBOL_H
#define TEXTEDITOR_INSERT_SYMBOL_H

#include "alllib.h"

int edit_string(struct stroki** Begin,struct stroki** End,int* kolSTR,int f);
int delete_braces(struct stroki** Begin,struct stroki** End,int* kolSTR,int f);
int replace_substring(struct stroki** Begin,struct stroki** End,int* kolSTR);

#endif /* TEXTEDITOR_INSERT_SYMBOL_H */
