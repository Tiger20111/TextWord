#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

#include "syscomand.h"


/*
 *              name_mistake
 *          Функция, которая говорит с какой ошибкой мы завершаем программу, а так же очищает память, а так же печатает ошибку, если необходимо
 *        Собственно возвращает и номер ошибки
 *      На вход принимает
 *
 *  int number                      номер ошибки, которая возникла в другой функции
 *  struct stroki ** Begin          указатель на  указатель на начало строк. Begin->next указывает на первую строку
 *  struct stroki ** End            указатель на указатель на конец строкю End указывает на последнюю строку.
 *  struct stroki ** BeginHelp      указатель на  указатель на начало описания команд по текстовому редактору. BeginHelp->next указывает на первую строку
 *  struct stroki ** EndHelp        указатель на  указатель на конец описания команд по текстовому редактору. EndHelp указывает на последнюю строку
 *
 */
int name_mistake(int number,struct stroki** Begin,struct stroki** BeginHelp)
{
    struct stroki* go;
    struct stroki* del;
    go=(*Begin)->next;
    if((go)!=NULL)
    {


        while (go != NULL)
        {
            del = go;
            go = go->next;
            free(del->s);
            free(del);
        }

    }

    go = (*BeginHelp)->next;

    if(go==NULL)
    {
        return number;
    }
    while (go!=NULL)
    {
        del=go;
        go=go->next;
        free (del->s);
        free(del);
    }
    switch(number)
    {

    case 0:
        return OK;
    case 2:
        wprintf(L"error input arguments");
        return ERROR_ARG;
    case 3:
        wprintf(L"error round file");
        return ERROR_OPEN_FILE;
    case 4:
        wprintf(L"error realloc");
        return LOCK;
    case 9:
        return OK;
    default:
        return 11;
    }

}

/*
 *                   set_name
 *           Функция, которая заполняет название файла для сохранения в него итога
 *        Возвращает код, с которым завершилась данная функция
 *     На вход принимает
 * char* setname           передаем массив, в котором будем хранить имя
 * int* setnamekol         передаем указатель на переменную, в которой в текущий момент хранится длина пути в символах
 * int* setnamemax         передаем указатель на переменную в которой хранится максимальная длина массива, в которой хранится путь, чтобы в случае необходимости расширить
 * char* setnewname        массив в котором может хранится путь к файлу, если передан size==1
 * int size                передаем флаг, который говорит откуда мы получаем путь. Из переданного массива setnewname или из ввода
 */

int set_name(char* setname,int *setnamekol,int *setnamemax,char * setnewname,int size )
{
    int i=0;
    char x='\0';
    int input=0;
    int exit_eof=0;
    if (size==0)
    input=fgetwc(stdin);
    if (input==EOF)
    {
        exit_eof=1;
        x='\n';
    }
    else
    {
        x=(char)input;
    }
    while (x==' ')
    {
        input=fgetwc(stdin);
        if (input==EOF)
        {
            exit_eof=1;
            x='\n';
        }
        else
        {
            x=(char)input;
        }
    }
    if(x!='"')
    {
        return ERROR_ARG;
    }
    if(size == 0)
    {
        input=fgetwc(stdin);
        if (input==EOF)
        {
            exit_eof=1;
            x='\n';
        }
        else
        {
            x=(char)input;
        }
    }
    else
    {
        x=setnewname[i];
        i++;
    }
    while (((size==0)&&((x!='\n')&&(x!='#'))) || ((size!=0)&&(i<=size)))
    {
        setname[i]=x;
        (*setnamekol)++;
        if ((*setnamekol)>=(*setnamemax))
        {
            setname = realloc(setname, (*setnamemax) * 2 * sizeof(wchar_t));
        }

        if (size==0)
        {
            input=fgetwc(stdin);
            if (input==EOF)
            {
                exit_eof=1;
                x='\n';
            }
            else
            {
                x=(char)input;
            }
        }
        else
        {
            x=setname[i];
        }
        i++;
    }
    if((x=='#')&&(size==0))
    {
        while(x!='\n')
        {
            input=fgetwc(stdin);
            if (input==EOF)
            {
                exit_eof=1;
                x='\n';
            }
            else
            {
                x=(char)input;
            }
        }
    }
    if (size==0)
    {
        setname[i-1]='\000';
        (*setnamekol)--;
    }
    if(exit_eof!=0)
    {
        return OK_EXIT;
    }
    else return OK;
}


/*
 *                      read_
 *          Функция, которая берет строки из файла, после чего замещает ими строки, которые хранятся у нас в списке
 *          так же в зависимости от токо вызывали мы ее как read или как open мы запоминаем путь к файлу для сохранения в него или нет.
 *       Возвращаем номер кода, с которым закочилась данная функция.
 *     На вход принимаем
 *  struct stroki ** Begin          указатель на  указатель на начало строк. Begin->next указывает на первую строку
 *  struct stroki ** End            указатель на указатель на конец строкю End указывает на последнюю строку.
 *  int* kolSTR                     указатель на переменную в которой хранится кол-во строк в списке в текущий момент
 *  char* setname                   передаем массив, в котором будет храниться путь до файла
 *  int* setnamekol                 передаем указатель на переменную в которой хранится текущее кол-во символов массива setname
 *  int* setnamemax                 передаем указатель на переменную в которой хранится максимальный размер массива setname
 *  int f                           флаг, который определяет, вызвали мы open или read. Если f==0, то read иначе open
 */


int read_(struct stroki** Begin,struct stroki** End,int* kolSTR,char * setname,int *setnamekol,int *setnamemax,int f)
{
    int y = 100;
    char* loc;
    int input;
    int exit_eof=0;
    wchar_t *locw;
    struct stroki *NewElement;
    char* u =(char*)malloc(100*sizeof(char));
    wchar_t* line =(wchar_t*)malloc(100*sizeof(wchar_t));
    int rk=100;
    int r=0;
    int sch =0;

    FILE* file;
    struct stroki* go;
    struct stroki* del;

    wchar_t c=L'\0';
    wchar_t now=L'\0';
    wchar_t next=L'\0';
    wchar_t control_=L'\0';


    int k=0;
    int i=0;


    char x;
    (*kolSTR)=0;
    input=fgetwc(stdin);
    if (input==EOF)
    {
        exit_eof=1;
        x='\n';
    }
    else
    {
        x=(char)input;
    }
    while (x==' ')
    {
        input=fgetwc(stdin);
        if (input==EOF)
        {
            exit_eof=1;
            x='\n';
        }
        else
        {
            x=(char)input;
        }

    }
    if (x != '"')
    {
        return ERROR_ARG;
    }
    input=fgetwc(stdin);
    if (input==EOF)
    {
        exit_eof=1;
        x='\n';
    }
    else
    {
        x=(char)input;
    }
    while ((x != '\n')&&(x!='#'))
    {
        u[sch] = x;
        sch = sch + 1;
        if (sch >= rk)
        {
            loc = realloc(u, rk * 2 * sizeof(wchar_t));
            if(loc)
            {
                while(x!='\n')
                {
                    input=fgetwc(stdin);
                    if (input==EOF)
                    {
                        exit_eof=1;
                        x='\n';
                    }
                    else
                    {
                        x=(char)input;
                    }
                }
                free(u);
                free(line);
                return LOCK;
            }
            else
            {
                u=loc;
            }
            rk = rk * 2;
        }
        input=fgetwc(stdin);
        if (input==EOF)
        {
            exit_eof=1;
            x='\n';
        }
        else
        {
            x=(char)input;
        }
    }
    if(x=='#')
    {
        while(x!='\n')
        {
            input=fgetwc(stdin);
            if (input==EOF)
            {
                exit_eof=1;
                x='\n';
            }
            else
            {
                x=(char)input;
            }
        }
    }
    if (u[sch - 1] != '"')
    {
        return ERROR_ARG;
    }
    else
    {
        sch = sch - 1;
        u[sch] = '\0';
    }


    file=fopen(u,"r");
    if (file==NULL)
    {
        free(u);
        free(line);
        return ERROR_OPEN_FILE;
    }
    if (f==1)
    {
        set_name(setname,setnamekol,setnamemax,u,sch);
    }

    go=(*Begin)->next;
    while ((go!=(*End)) && (go!=NULL))
    {

        del=go;
        go=go->next;
        free (del->s);
        free(del);

    }
    if((*Begin)->next!=NULL) {
        free((*End)->s);
        free(*End);
    }
    (*End)=(*Begin);
    (*End)->prev=(*Begin);
    (*Begin)->next=(*End);
    (*End)->next=NULL;
    del=NULL;
    go=NULL;
    while(1)
    {
        wint_t wc;
        wc = fgetwc(file);
        control_ = now;
        now = next;
        next = wc;


        if ((control_ == L'\\') && (now == L'\\') && ((next == L'n') || (next == L'r') || (next == L't')))
        {
            now = next;
            wc = fgetwc(file);
            next = wc;

        }
        else
        {
            while (((control_ != L'\\')||(control_==L'\000')) && (now == L'\\') && ((next == L'n') || (next == L'r') || (next == L't')))
            {


                if (next == L'r')
                {
                    control_=L'\0';
                    now = L'\r';
                    wc = fgetwc(file);
                    next = wc;
                }
                if (next == L't')
                {
                    control_=L'\0';
                    now = L'\t';
                    wc = fgetwc(file);
                    next = wc;
                }
                if (next == L'n')
                {
                    now = L'\n';
                    next = L'\0';
                    control_=L'\0';
                }
            }
            c = now;
            if ((c != L'\n'))
            {
                if (wc == WEOF)
                {
                    fclose(file);
                    free(line);
                    free(u);
                    break;
                }
                if (i < y)
                {
                    if(c!=L'\0')
                    {
                        line[i] = c;
                        k++;
                        i++;
                    }

                    if (next==L'\n')
                    {
                        NewElement = calloc(1, sizeof(struct stroki));

                        (*kolSTR)++;
                        NewElement->s = line;
                        NewElement->prev = (*End);

                        NewElement->sizeS = k;

                        if((*End)!=NULL)
                        {
                            (*End)->next = NewElement;
                        }

                        (*End) = NewElement;
                        (*End)->next = NULL;

                        c=L'\0';
                        now=L'\0';
                        next=L'\0';
                        control_=L'\0';
                        line = (wchar_t *) malloc(100 * sizeof(wchar_t));

                        if(!r)
                        {
                            (*Begin)->next=NewElement;
                            r=1;
                        }
                        y = 100;
                        k = 0;
                        i = 0;

                    }

                }
                else
                {

                    locw = realloc(line, y * 2 * sizeof(wchar_t));
                    if(locw==NULL)
                    {
                        fclose(file);
                        free(line);
                        free(u);
                        return LOCK;
                    }
                    else
                    {
                        line=locw;
                    }
                    y = y * 2;
                }
            }

            else
            {


                if (wc == WEOF)
                {
                    fclose(file);
                    free(line);
                    free(u);
                    break;
                }
            }
        }

    }
    if(exit_eof==1)
        return OK_EXIT
    else return OK;
}


/*
 *                  write_
 *              Функция, которая записывает весь текст, который хранится в списке.
 *        На выход выдает код с которым завершилась данная функция
 *     На вход принимает
 *  struct stroki ** Begin          указатель на  указатель на начало строк. Begin->next указывает на первую строку
 *  struct stroki ** End            указатель на указатель на конец строкю End указывает на последнюю строку.
 *  int* kolSTR                     указатель на переменную в которой хранится кол-во строк в списке в текущий момент
 *  char* setname                   передаем массив, в храниться путь до файла
 *  int* setnamekol                 передаем указатель на переменную в которой хранится текущее кол-во символов массива setname
 *  int* setnamemax                 передаем указатель на переменную в которой хранится максимальный размер массива setname
 *  int logic                       флаг, который говорит, передадут ли нам путь до файла, в который надо записывать или надо использовать путь, который указан в setname
 *
 */



int write_(struct stroki** Begin,char * setname,int *setnamekol,int *setnamemax,int logic)
{
    int i=0;
    char* loc;
    int input;
    struct stroki* go;
    int exit_eof;
    FILE* file;
    exit_eof=0;
    if(logic)
    {
        char* u =(char*)malloc(100*sizeof(char));
        int rk=100;
        int sch =0;

        char x;


        input=fgetwc(stdin);
        if (input==EOF)
        {
            free(u);
            return ERROR_INPUT;
        }
        else
        {
            x=(char)input;
        }

        while (x==' ')
        {
            input=fgetwc(stdin);
            if (input==EOF)
            {
                free(u);
                return ERROR_INPUT;
            }
            else
            {
                x=(char)input;
            }
        }
        if (x != '"')
        {
            return ERROR_ARG;
        }
        input=fgetwc(stdin);
        if (input==EOF)
        {
            free(u);
            return ERROR_INPUT;
        }
        else
        {
            x=(char)input;
        }
        while ((x != '\n')&&(x!='#'))
        {
            u[sch] = x;
            sch = sch + 1;
            if (sch >= rk)
            {
                loc = realloc(u, rk * 2 * sizeof(wchar_t));
                if (loc==NULL)
                {
                    while(x!='\n')
                    {
                        input=fgetwc(stdin);
                        if (input==EOF)
                        {
                            exit_eof=1;
                            x='\n';
                        }
                        else
                        {
                            x=(char)input;
                        }
                    }
                    free(u);
                    return LOCK;
                }
                else
                {
                    u=loc;
                }
                rk = rk * 2;
            }
            input=fgetwc(stdin);
            if (input==EOF)
            {
                exit_eof=1;
                x='\n';
            }
            else
            {
                x=(char)input;
            }
        }
        if(x=='#')
        {
            while(x!='\n')
            {
                input=fgetwc(stdin);
                if (input==EOF)
                {
                    x='\n';
                    exit_eof=1;
                }
                else
                {
                    x=(char)input;
                }
            }
        }
        if (u[sch - 1] != '"')
        {
            free(u);
            return ERROR_ARG;
        }
        else
        {
            sch = sch - 1;
            u[sch] = '\0';
        }

        if (setnamekol==0)
        {
            set_name(setname,setnamekol,setnamemax,u,sch);
        }

        file=fopen(u,"w");
        if (file==NULL)
        {
            free(u);
            return ERROR_OPEN_FILE;
        }

        go=(*Begin)->next;
        while(go!= NULL)
        {
            for (i=0; i<go->sizeS; i++)
            {

                fwprintf(file,L"%lc",go->s[i]);
                /*fputwc(go->s[i],file);*/

            }
            fwprintf(file,L"\n");

            /*   fputwc(L'\n',file);*/
            go=go->next;
        }
        free(u);
        fclose(file);
    }
    else
    {
        if (setnamekol)
        {
            file = fopen(setname, "w");

            go = (*Begin)->next;
            while (go != NULL)
            {
                for (i = 0; i < go->sizeS; i++)
                {

                    fwprintf(file,L"%lc",go->s[i]);
                    /*fputwc(go->s[i], file);*/

                }
                fwprintf(file,L"\n");
                /*fputwc(L'\n', file);*/
                go = go->next;
            }
            fclose(file);
        }
        else
        {
            return ERROR_ARG; /*ВАЖНО*/
        }
    }

    if(exit_eof) {return OK_EXIT;}
    else {return OK;}
}


