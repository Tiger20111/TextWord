#ifndef TEXTEDITOR_ALLLIB_H
#define TEXTEDITOR_ALLLIB_H

#include <wchar.h>

#define OK 0;
#define NO_COM 1;
#define ERROR_ARG 2;
#define LOCK 4;
#define OK_EXIT 9;
#define ERROR_OPEN_FILE 3;
#define ERROR_INPUT 5;

struct stroki
{
    wchar_t * s;
    int sizeS;
    struct stroki* next;
    struct stroki* prev;

};

int zifra(wchar_t x);
int get_int(wchar_t **_buf, int* a);

#endif
