#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

#include "call_command.h"
#include "parsing_command.h"

/*
 *                              command
 *                  Функция, которая выдает приглашение к вводу и собственно регулирует, мы заканчиваем ввод или нет. А так же вызывает функцию, которая определяет, какую функцию по введенной строке надо вызвать
 *          Возвращает код, с котором завершилась одна из вызванных функций, если с ошибкой или с 0, если был вызван выход
 *      На вход принимает
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
 */


int command(struct stroki** Begin,
            struct stroki** End,
            int* kolSTR,
            int* numbers,
            int* wrap,
            int* tab,
            struct stroki** BeginHelp,
            int* kolHelp,
            char * setname,
            int *setnamekol,
            int *setnamemax )
{
    int nocom=0;
    int k;
    int r;
    int exit_eof=0;
    int comment=0;
    int logic=0;

    int y=0;
    wchar_t input[25];

    int count=0;

    int i=0;
    wint_t inputr;

    for(y=0; y<20; y++)
    {
        input[y]=L'\n';
    }
    while(1)
    {
        if(*End) (*End)->next=NULL;
        nocom=0;
        wprintf(L"Editor: ");
        y=0;

        i=0;
        count=0;
        logic=0;
        while(1)

        {


            y++;
            inputr=fgetwc(stdin);
            if (inputr==WEOF)
            {
              exit_eof=1;
              input[i]='\n';
            }
            else
            {
                input[i]=(int)inputr;
            }
            while(input[0]==L' ')
            {
                inputr=fgetwc(stdin);

                if (inputr==WEOF)
                {
                    exit_eof=1;
                    input[0]='\n';
                }
                else
                {
                    input[0]=(int)inputr;
                }

            }
            if(input[0]==L'#')
            {
                input[1]=L'1';
                while(input[1]!=L'\n')
                {
                    inputr=fgetwc(stdin);
                    if (inputr==WEOF)
                    {
                        exit_eof=1;
                        input[1]='\n';
                    }
                    else
                    {
                        input[1]=inputr;
                    }
                }
                comment=1;
                break;
            }

            if ((input[i]==L'\n')||(input[i]==L'#'))
            {
                if(input[i]==L'#')
                {
                    while(input[i]!=L'\n')
                    {
                        inputr=fgetwc(stdin);
                        if (inputr==WEOF)
                        {
                            exit_eof=1;
                            input[i]='\n';
                        }
                        else
                        {
                            input[i]=inputr;
                        }
                    }
                }
                logic=0;
                break;
            }
            if((input[i]==L' ')  )
            {

                logic=1;
                break;
            }

            count++;
            i++;
            if(count>18)
            {
                nocom=1;
                logic=2;
                break;

            }
            if (comment==1)
            {
                comment=0;
                if(exit_eof==1)
                    return OK_EXIT;
                continue;
            }
        }

        i=0;

        if((count==0))
        {
            if(exit_eof==1)
                return OK_EXIT;
            continue;
        }

        if (logic==0)
        {
            r = zapusk(input, count,Begin,End,kolSTR,numbers,wrap,tab,BeginHelp,kolHelp, setname,setnamekol,setnamemax,logic );
            if (r!=0)
            {
                if (r!=1 && r!=2&& r!=3&&r!=5 )
                {
                    return r;
                }
                else
                {
                    if (r==1)  wprintf(L"No such command:    ");
                    if (r==2)
                    {
                        wprintf(L"Error arguments in:   ");
                        for (i=0; i<count; i++)
                        {
                            wprintf(L"%lc",input[i]);
                        }
                        wprintf(L"\n");
                        continue;
                    }
                    if (r==3)
                    {

                        wprintf(L"Error open file in:    ");
                        for (i=0; i<count; i++)
                        {
                            wprintf(L"%lc",input[i]);
                        }
                        wprintf(L"\n");
                        continue;
                    }
                    if (r==5)
                    {
                        wprintf(L"Error input in:    ");
                        for (i=0; i<count; i++)
                        {
                            wprintf(L"%lc",input[i]);
                        }
                        wprintf(L"\n");
                        continue;
                    }   for (i=0; i<count; i++)
                    {
                        wprintf(L"%lc",input[i]);
                    }
                    wprintf(L"\n");
                    if(exit_eof==1)
                        return OK_EXIT;
                    continue;
                }
            }
        }
        if (logic==1)
        {
            r = zapusk(input, count, Begin, End, kolSTR,numbers,wrap,tab,BeginHelp,kolHelp, setname,setnamekol,setnamemax,logic);
            if (r != 0)
            {
                if (r == 1||r==2|| r==3||r==5)
                {
                    if (r==2)
                    {
                        wprintf(L"Error arguments in:   ");
                        for (i=0; i<count; i++)
                        {
                            wprintf(L"%lc",input[i]);
                        }
                        wprintf(L"\n");
                        continue;
                    }
                    if (r==3)
                    {

                        wprintf(L"Error open file in:    ");
                        for (i=0; i<count; i++)
                        {
                            wprintf(L"%lc",input[i]);
                        }
                        wprintf(L"\n");
                        continue;
                    }
                    if (r==5)
                    {
                        wprintf(L"Error input in:    ");
                        for (i=0; i<count; i++)
                        {
                            wprintf(L"%lc",input[i]);
                        }
                        wprintf(L"\n");
                        continue;
                    }
                    nocom = 0;
                    count++;
                    i = count;
                    k = 0;
                    while (1)
                    {

                        y++;

                        inputr=fgetwc(stdin);
                        if (inputr==WEOF)
                        {
                            exit_eof=1;
                            input[i]='\n';
                        }
                        else
                        {
                            input[i]=inputr;
                        }

                        if (input[i] != L'\n' && input[i] != L' '&&input[i]!=L'#')
                        {

                            k = 1;
                        }

                        if ((input[i]==L'#' || input[i] == L'\n' || input[i] == L' ') && (k == 1))
                        {
                            if (input[i]==L' ')
                            {
                                logic=1;
                                nocom=2;
                            }
                            if ((input[i]==L'\n')||(input[i]==L'#'))
                            {
                                if(input[i]==L'#')
                                {
                                    while(input[i]!=L'\n')
                                    {
                                        inputr=fgetwc(stdin);
                                        if (inputr==WEOF)
                                        {
                                            exit_eof=1;
                                            input[i]='\n';
                                        }
                                        else
                                        {
                                            input[i]=inputr;
                                        }
                                    }
                                }
                                logic=0;
                            }
                            break;
                        }
                        if (input[i] != L' ')
                        {
                            count++;
                            i++;
                            if (count > 18)
                            {
                                nocom = 1;
                                break;

                            }
                        }
                    }


                    if (nocom != 1)
                    {
                        r = zapusk(input, count, Begin, End, kolSTR,numbers,wrap,tab,BeginHelp,kolHelp, setname,setnamekol,setnamemax,logic);
                    }
                    if (r == 1|| r==2|| r==3||r==5 || nocom == 1)
                    {
                        if (r==1)  wprintf(L"No such command:    ");
                        if (r==2)
                        {
                            wprintf(L"Error arguments in:   ");
                            for (i=0; i<count; i++)
                            {
                                wprintf(L"%lc",input[i]);
                            }
                            wprintf(L"\n");
                            continue;
                        }
                        if (r==3)
                        {

                            wprintf(L"Error open file in:    ");
                            for (i=0; i<count; i++)
                            {
                                wprintf(L"%lc",input[i]);
                            }
                            wprintf(L"\n");
                            continue;
                        }
                        if (r==5)
                        {
                            wprintf(L"Error input in:    ");
                            for (i=0; i<count; i++)
                            {
                                wprintf(L"%lc",input[i]);
                            }
                            wprintf(L"\n");
                            continue;
                        }for (i=0; i<count; i++)
                        {
                            wprintf(L"%lc",input[i]);
                        }
                        if (nocom == 1 || nocom==2)
                        {


                            while(input[0]!=L'\n')
                            {
                                inputr=fgetwc(stdin);
                                if (inputr==WEOF)
                                {
                                    exit_eof=1;
                                    input[0]='\n';
                                }
                                else
                                {
                                    input[0]=inputr;
                                }
                                wprintf(L"%lc",input[0]);
                            }




                        }
                        if(exit_eof==1)
                            return OK_EXIT;
                        continue;
                    }
                    else
                    {
                        if(r==0)
                        {
                            if(exit_eof==1)
                                return OK_EXIT;
                            continue;
                        }
                       else
                        {
                            return r;
                        }
                    }

                }
                else
                {
                    return r;
                }
            }
        }
        if(logic==2)
        {
            wprintf(L"No such command:    ");

            for (i=0; i<count; i++)
            {
                wprintf(L"%lc",input[i]);
            }
            while(input[0]!=L'\n')
            {
                inputr=fgetwc(stdin);
                if (inputr==WEOF)
                {
                    exit_eof=1;
                    input[0]='\n';
                }
                else
                {
                    input[0]=inputr;
                }
                wprintf(L"%lc",input[0]);
            }
            if(exit_eof==1)
                return OK_EXIT;
            continue;

        }

    }
    return OK;
}
