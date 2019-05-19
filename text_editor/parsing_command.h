#ifndef TEXTEDITOR_PARSING_COMMAND_H
#define TEXTEDITOR_PARSING_COMMAND_H

#include <wchar.h>

#include "alllib.h"

int zapusk( wchar_t* input,
            int count,
            struct stroki** Begin,
            struct stroki** End,
            int* kolSTR,
            int* numbers,
            int* wrap,
            int* tab,
            struct stroki** BeginHelp,
            int* kolHelp,
            char * setname,
            int *setnamekol,
            int *setnamemax,
            int logic
         );
#endif
