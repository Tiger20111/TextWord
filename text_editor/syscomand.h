#ifndef TEXTEDITOR_SYSCOMMAND_H
#define TEXTEDITOR_SYSCOMMAND_H

#include "alllib.h"

int name_mistake( int number,
                  struct stroki** Begin,
                  struct stroki** BeginHelp
                );

int read_( struct stroki** Begin,
           struct stroki** End,
           int* kolSTR,
           char * setname,
           int *setnamekol,
           int *setnamemax,
           int f
         );

int set_name( char* setname,
              int *setnamekol,
              int *setnamemax,
              char * setnewname,
              int size
            );

int write_( struct stroki** Begin,
            char * setname,
            int *setnamekol,
            int *setnamemax,
            int logic
          );
#endif
