#ifndef TEXTEDITOR_INSERT_AFTERS_H
#define TEXTEDITOR_INSERT_AFTERS_H

#include <wchar.h>
#include "alllib.h"

int insert_after(struct stroki** Begin,struct stroki** End,int* kolSTR,int z,wchar_t *string, int nom);
int delete_range(struct stroki** Begin,struct stroki** End,int* kolSTR);

#endif
