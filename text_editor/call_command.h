#ifndef TEXTEDITOR_CALL_COMMAND_H
#define TEXTEDITOR_CALL_COMMAND_H

#include "alllib.h"

int command( struct stroki** Begin,
             struct stroki** End,
             int* kolSTR,
             int* numbers,
             int* wrap,
             int* tab,
             struct stroki** BeginHelp,

             int* kolHelp,
             char * setname,
             int *setnamekol,
             int *setnamemax
           );

#endif /* TEXTEDITOR_CALL_COMMAND_H */
