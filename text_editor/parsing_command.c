#define  _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <wchar.h>

#include "printf.h"
#include "parsing_command.h"
#include "insert_symbol.h"
#include "insert_afters.h"
#include "syscomand.h"


/*
 *                      zapusk
 *                Функция, которая вызывает нужную функцию, название которой передано в массиве input
 *          Возвращает код с которым завершилась эта функция, если не нашла соответствующей, или код с которым завершилась одна из вызываемых функций
 *    На вход принимает
 * wchar_t* input                           массив, в котором записано название, вызываемой функции
 * int count                                переменная, в которой записана длина массива input
 * struct stroki ** Begin                   указатель на  указатель на начало строк. Begin->next указывает на первую строку
 * struct stroki ** End                     указатель на указатель на конец строкю End указывает на последнюю строку.
 * int* kolSTR                              указатель на переменную в которой хранится кол-во строк в списке в текущий момент
 * int* numbers                             Указатель на переменную, которая говорит, включен ли вывод номеров строк
 * int* wrap                                Указатель на переменную, которая говорит, включено ли обрезание строк
 * int* tab                                 Указатель на переменную, в которой хранится число. На это кол-во пробелов заменяется tab
 * struct stroki ** BeginHelp               указатель на  указатель на начало описания команд по текстовому редактору. BeginHelp->next указывает на первую строку
 * struct stroki ** EndHelp                 указатель на  указатель на конец описания команд по текстовому редактору. EndHelp указывает на последнюю строку
 * int* kolHelp                             указатель на переменную, в которой хранится колличество строк в тексте HELP
 * char* setname                            передаем массив, в котором будет храниться путь до файла
 * int* setnamekol                          передаем указатель на переменную в которой хранится текущее кол-во символов массива setname
 * int* setnamemax                          передаем указатель на переменную в которой хранится максимальный размер массива setname
 * int logic                                переменная, которая говорит, будут ли аргументы у вызванной функции
 */
/*
struct command
{
    enum comm_name
    char *args[4]
    int actual_arguments;

};

int parse_command(FILE *f,struct command *com)
*/

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
          )
{
    switch(count)
    {
    case 4:
        if((input[0]==L'e') && (input[1]==L'x') && (input[2]==L'i') && (input[3]==L't'))
        {
            if (logic==0)
            {
                if ((!(*setnamekol))&&((*kolSTR)))
                {
                    wprintf(L"not found save file\n");
                    return OK;
                }
                else
                {
                    return OK_EXIT;
                }
            }
            if (logic==1)
            {
                wint_t x;
                wchar_t e[5];
                int y=0;

                x=fgetwc(stdin);
                if(x==WEOF)
                {
                    x='\n';
                }

                while(y<5)
                {
                    if(x==L'\n' || x==L'#')
                    {
                        while(x!=L'\n' )
                        {
                            x=fgetwc(stdin);
                        }
                        return NO_COM;
                    }
                    e[y]=x;
                    y++;
                    x=fgetwc(stdin);
                    if(x==WEOF)
                    {
                        x='\n';
                    }

                }
                if ((e[0]==L'f' && e[1]==L'o' && e[2]==L'r' && e[3]==L's' && e[4]==L'e')==0 )
                {
                    return ERROR_ARG;
                }
                if (x==L'#')
                {
                    while(x!=L'\n')
                    {
                        x=fgetwc(stdin);
                        if(x==WEOF)
                        {
                            x='\n';
                        }
                    }
                }
                if (x==L'\n')
                {
                    return OK_EXIT;
                }
                else
                {
                    return ERROR_ARG;
                }

            }
            return OK_EXIT;

        }
        if((input[0]==L'r') && (input[1]==L'e') && (input[2]==L'a') && (input[3]==L'd'))
        {
            return read_(Begin,End, kolSTR,setname,setnamekol,setnamemax,0);
        }
        if((input[0]==L'o') && (input[1]==L'p') && (input[2]==L'e') && (input[3]==L'n'))
        {
            return read_(Begin,End, kolSTR,setname,setnamekol,setnamemax,1);
        }
        if((input[0]==L'h') && (input[1]==L'e') && (input[2]==L'l') && (input[3]==L'p'))
        {
            return print_pages(BeginHelp,numbers,wrap,tab,1,(*kolHelp),(*kolHelp));
        }

            return NO_COM;




    case 5:
        if((input[0]==L'w') && (input[1]==L'r') && (input[2]==L'i') && (input[3]==L't') && (input[4]==L'e'))
        {
           return write_( Begin,setname,setnamekol,setnamemax, logic);
        }
            return NO_COM;


    case 8:
        if((input[0]==L's') && (input[1]==L'e') && (input[2]==L't') && (input[3]==L' ') && (input[4]==L'n')&& (input[5]==L'a') && (input[6]==L'm') && (input[7]=L'e'))
        {
            return set_name(setname,setnamekol,setnamemax, NULL, 0 );
        }

        if((input[0]==L's') && (input[1]==L'e') && (input[2]==L't') && (input[3]==L' ') && (input[4]==L'w')&& (input[5]==L'r') && (input[6]==L'a') && (input[7]==L'p'))
        {
            return set_wrap(wrap);
        }
            return NO_COM;


    case 11:
        if((input[0]==L's') && (input[1]==L'e') && (input[2]==L't') && (input[3]==L' ') && (input[4]==L'n')&& (input[5]==L'u') && (input[6]==L'm') && (input[7]==L'b')&& (input[8]==L'e') && (input[9]==L'r') && (input[10]==L's'))
        {
            return set_numbers(numbers);
        }

        if((input[0]==L'p') && (input[1]==L'r') && (input[2]==L'i') && (input[3]==L'n') && (input[4]==L't')&& (input[5]==L' ') && (input[6]==L'p') && (input[7]==L'a')&& (input[8]==L'g') && (input[9]==L'e') && (input[10]==L's'))
        {
            return print_pages(Begin,numbers,wrap,tab,1,(*kolSTR),(*kolSTR));
        }

        if((input[0]==L'p') && (input[1]==L'r') && (input[2]==L'i') && (input[3]==L'n') && (input[4]==L't')&& (input[5]==L' ') && (input[6]==L'r') && (input[7]==L'a')&& (input[8]==L'n') && (input[9]==L'g') && (input[10]==L'e'))
        {
            return print_range(Begin,numbers,wrap,tab,kolSTR);

        }
        if((input[0]==L'e') && (input[1]==L'd') && (input[2]==L'i') && (input[3]==L't') && (input[4]==L' ')&& (input[5]==L's') && (input[6]==L't') && (input[7]==L'r')&& (input[8]==L'i') && (input[9]==L'n') && (input[10]==L'g'))
        {
            return edit_string( Begin, End, kolSTR,0);
        }
            return NO_COM;


    case 12:

        if((input[0]==L'i') && (input[1]==L'n') && (input[2]==L's') && (input[3]==L'e') && (input[4]==L'r')&& (input[5]==L't') && (input[6]==L' ') && (input[7]==L'a')&& (input[8]==L'f') && (input[9]==L't') && (input[10]==L'e')&& (input[11]==L'r'))
        {
            return insert_after(Begin,End,kolSTR,0,NULL,0);

        }
        if((input[0]==L'd') && (input[1]==L'e') && (input[2]==L'l') && (input[3]==L'e') && (input[4]==L't')&& (input[5]==L'e') && (input[6]==L' ') && (input[7]==L'r')&& (input[8]==L'a') && (input[9]==L'n') && (input[10]==L'g')&& (input[11]==L'e'))
        {
            return delete_range(Begin,End,kolSTR);
        }
        if((input[0]==L's') && (input[1]==L'e') && (input[2]==L't') && (input[3]==L' ') && (input[4]==L't')&& (input[5]==L'a') && (input[6]==L'b') && (input[7]==L'w')&& (input[8]==L'i') && (input[9]==L'd') && (input[10]==L't')&& (input[11]==L'h'))
        {
            return set_tabwidth(tab);
        }
            return NO_COM;

    case 13:
        if((input[0]==L'i') && (input[1]==L'n') && (input[2]==L's') && (input[3]==L'e') && (input[4]==L'r')&& (input[5]==L't') && (input[6]==L' ') && (input[7]==L's')&& (input[8]==L'y') && (input[9]==L'm') && (input[10]==L'b')&& (input[11]==L'o')&& (input[12]==L'l'))
        {
            return edit_string( Begin, End, kolSTR,1);
        }
        if((input[0]==L'd') && (input[1]==L'e') && (input[2]==L'l') && (input[3]==L'e') && (input[4]==L't')&& (input[5]==L'e') && (input[6]==L' ') && (input[7]==L'b')&& (input[8]==L'r') && (input[9]==L'a') && (input[10]==L'c')&& (input[11]==L'e')&& (input[12]==L's'))
        {
            return delete_braces( Begin, End, kolSTR, logic);
        }
            return NO_COM;

    case 17:
        if((input[0]==L'r') && (input[1]==L'e') && (input[2]==L'p') && (input[3]==L'l') && (input[4]==L'a')&& (input[5]==L'c') && (input[6]==L'e') && (input[7]==L' ')&& (input[8]==L's') && (input[9]==L'u') && (input[10]==L'b')&& (input[11]==L's')&& (input[12]==L't')&& (input[13]==L'r')&& (input[14]==L'i') && (input[15]==L'n') && (input[16]==L'g'))
        {
            return  replace_substring(Begin,End,kolSTR);
        }
            return NO_COM;

    default:
        return NO_COM;
    }

}

