#define _POSIX_C_SOURCE 200112L

#include <sys/ioctl.h>
#include <termios.h>

/*
 * for STDIN_FILENO
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "printf.h"


/*
 *                  mygetch
 *           Функция, которая делает так, что в терминале нажатие на клавиши сразу передается в терминал.
 *       Возвращает код символа, который был передан терминалу
 */


wint_t mygetch( )
{
    struct termios oldt,
            newt;
    wint_t ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = fgetwc(stdin);
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

/*
 *                    set_numbers
 *               Функция, которая включает или выключает вывод номеров при выводе строк на экран
 *         Возвращает код функции, с которым она завершилась
 *     На вход принимает
 * int * numbers   переменная, в которой хранится 1, если у нас включена подсветка номеров строк или 0 иначе
 */

int set_numbers(int* numbers)
{
    wint_t input;
    int exit_eof=0;
    int logic=0;
    int count=0;
    wint_t x=L'\0';

    wchar_t arg[4];

    input=fgetwc(stdin);
    if (input==WEOF)
    {
        exit_eof=1;
        x=L'\n';
    }
    else
    {
        x=input;
    }
    while (x==L' ')
    {
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }
    }
    while ((x!=L'\n')&&(x!=L'#'))
    {
        if (count>2)
        {
            logic=1;
            break;
        }
        arg[count]=x;
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }
        count=count+1;

    }
    if (x == L'#')
    {
        while (x != L'\n')
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                x=L'\n';
            }
            else
            {
                x=input;
            }
        }
    }

    if (count==0)
    {
        return ERROR_ARG;
    }

    if (logic==0)
    {
        if ((arg[0]==L'y')&&(arg[1]==L'e')&&(arg[2]==L's'))
        {
            (*numbers)=1;
        }
        else
        {
            if ((arg[0]==L'n')&&(arg[1]==L'o'))
            {
                (*numbers)=0;
            }
            else
            {
                return ERROR_ARG;
            }
        }

    }
    if (logic==1)
    {
        while (x != L'\n')
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                x=L'\n';
            }
            else
            {
                x=input;
            }
        }
        return ERROR_ARG;
    }
    if(exit_eof==1)
        return OK_EXIT
    else
        return OK;
}


/*
 *                  set_tabwidth
 *             Функция которая говорит, сколькими пробелами мы заменяем tab при выводе на экран
 *        Возвращает код, с которым завершилась данная функция
 *     На вход принимает
 * int* tab                   указатель на переменную в которой хранится кол-во пробелов, на которые мы заменим tab
 */


int set_tabwidth(int* tab)
{
    wint_t input;
    int exit_eof=0;
    wchar_t* arguments1 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor1;
    wchar_t* loc;
    int r=0;
    int arg_size=1;
    wchar_t x;
    int logic;
    int j;
    input=fgetwc(stdin);
    if (input==WEOF)
    {
        exit_eof=1;
        x=L'\n';
    }
    else
    {
        x=input;
    }
    while (x==L' ')
    {
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }
    }
    j=-1;
    logic =0;

    while(zifra(x))
    {
        logic=1;

        j=j+1;
        if(j==(arg_size)-1)
        {
            loc=realloc(arguments1,2*arg_size*sizeof(wchar_t));
            if (loc==NULL)
            {
                while(x!=L'\n')
                {
                    input=fgetwc(stdin);
                    if (input==WEOF)
                    {
                        exit_eof=1;
                        x=L'\n';
                    }
                    else
                    {
                        x=input;
                    }
                }
                free(arguments1);
                return LOCK;
            }
            else
            {
                arguments1=loc;
            }
            arg_size=arg_size*2;
        }
        arguments1[j]=x;
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }

    }
    if (x == L'#')
    {
        while (x != L'\n')
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                x=L'\n';
            }
            else
            {
                x=input;
            }
        }
    }

    if(logic==1)
    {

        arguments1[j+1]=L'\0';
        cursor1 = arguments1;

        get_int(&cursor1, &r);
        (*tab)=r;
        free (arguments1);
        if(exit_eof==1)
            return OK_EXIT
        else
            return OK;
    }

    else
    {
        free (arguments1);
        return ERROR_ARG;
    }

}


/*
 *                  set_wrap
 *          Функция, которая говорит, обрезаем ли мы строки или нет
 *      Возвращает код функции, с которой она завершилась
 *    На вход принимает
 * int* wrap          указатель на переменную, в которой хранится 1, если обрезаются строки и 0 иначе
 */


int set_wrap(int* wrap)
{
    int logic=0;
    int count=0;
    wint_t input;
    int exit_eof=0;
    wchar_t x=L'\0';
    wchar_t arg[4];
    input=fgetwc(stdin);
    if (input==WEOF)
    {
        exit_eof=1;
        x=L'\n';
    }
    else
    {
        x=input;
    }
    while (x==L' ')
    {
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }
    }
    while (x!=L'\n' && x!=L'#')
    {
        if (count>2)
        {
            logic=1;
            break;
        }
        arg[count]=x;
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }
        count=count+1;

    }
    if (x == L'#')
    {
        while (x != L'\n')
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                x=L'\n';
            }
            else
            {
                x=input;
            }
        }
    }
    if (count==0)
    {
        return ERROR_ARG;
    }

    if (logic==0)
    {
        if ((arg[0]==L'y')&&(arg[1]==L'e')&&(arg[2]==L's'))
        {
            (*wrap)=1;
        }
        else
        {
            if ((arg[0]==L'n')&&(arg[1]==L'o'))
            {
                (*wrap)=0;
            }
            else
            {
                return ERROR_ARG;
            }
        }

    }
    if (logic==1)
    {
        while (x != L'\n')
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                x=L'\n';
            }
            else
            {
                x=input;
            }
        }
        return ERROR_ARG;
    }
   if(exit_eof==1)
       return OK_EXIT
    else
       return OK;
}

/*
 *                      print_pages
 *               функция, котороя печатает текст, который хранится в списке, в зависимости от переданных в нее требований.
 *         Возвращает код, с которым завершилась данная функция
 *    На вход принимает
 * struct stroki** Begin                     Указатель на начало списка, в котором хранится текст. Begin->next указывает на первую строку
 * int* numbers                              Указатель на переменную, которая говорит, включен ли вывод номеров строк
 * int* wrap                                 Указатель на переменную, которая говорит, включено ли обрезание строк
 * int* tab                                  Указатель на переменную, в которой хранится число. На это кол-во пробелов заменяется tab
 * int num1                                  Переменная, которая говорит, с какой строки мы печатаем
 * int num2                                  Переменная, которая говорит, до какой строки, включая ее, мы печатаем
 * int kolSTR                                Переменная, которая передает кол-во строк в списке
 */

int print_pages(struct stroki** Begin,int* numbers,int* wrap,int* tab,int num1,int num2,int  kolSTR)
{
    /*  int fd = open("/dev/ttyS0", O_RDONLY);*/


    int e=0;
    int h=num1;
    int height=1;
    int nowsize=0;
    int f=0;
    int j;
    int n=0;
    int size=0;
    int maxlength =0;
    int logic=0;
    int logic2=0;
    int logic3=0;
    int logictab=0;
    int logictab2=0;
    int nowstr=1;
    struct stroki* go;
    struct stroki* len;
    struct stroki* end;
    int m;
    int k;
    int fix;
    int u;
    wint_t y;
    struct winsize g;

    if(isatty(1))
    {
        ioctl(1, TIOCGWINSZ, &g);
    }
    else
    {
        g.ws_row=0;    
    }
    
    if(!g.ws_col) g.ws_col=172;

    if(num1<1)
    {
        num1=1;
    }
    if(num2>=(kolSTR))
    {
        num2=kolSTR;
    }
    go = (*Begin);
    end=(*Begin)->next;
    for (e=0; e<num1; e++)
    {
        if(go)
        {
            go=go->next;
        }
        else break;
    }
    nowstr=num1;
    if(num2<=(kolSTR))
    {
        for (e = 0; e < num2; e++)
        {
            if (end)
            {
                end = end->next;
            }
            else break;
        }
    }
    else
    {
        end=NULL;
    }
    len=(*Begin)->next;
    if(!(*wrap))
    {
        for (e = num1; e < num1 + g.ws_row; e++)
        {
            if (len->sizeS > maxlength)
            {
                maxlength = len->sizeS;
            }
            len = len->next;
            if (!len)
            {
                break;
            }
        }
    }

    if(go!=NULL) size=go->sizeS;
     m=0;
    while(go!=end)
    {

        if(((*numbers)==1)&&(((*wrap)==0)||(logic==0)))
        {
            wprintf(L"%d:",h);
            logic=1;
            if((*wrap))
            {
                h = h + 1;
            }


        }
         j=0;

        {
            for (j = nowsize; j < go->sizeS; j++)
            {
                if(go->s[j]!=L'\t')
                {
                    wprintf(L"%lc", go->s[j]);
                }
                else
                {
                    logictab=1;


                }

                if ((logic3==0)&&(*numbers))
                {
                    k=h;
                    if (logictab2==0)
                    {
                        m=1;
                    }
                    else
                    {
                        m=m+1;
                    };
                    while (k!=0)
                    {
                        m=m+1;
                        k=k/10;
                    }
                    logic3=1;
                }
                else
                {
                    if ((!*numbers)&&(logictab2==0))
                    {
                        m=0;
                    }
                }
                if (logictab==1)
                {
                    logictab=0;

                    if(logictab2==0)
                    {
                        logictab2=1;
                        for (f = 0; f < (*tab); f++)
                        {
                            wprintf(L" ");
                        }
                        m = m + (*tab);
                    }
                }
                if (((j+1)>=go->sizeS)&&(*wrap))
                {
                    nowsize=size;
                    j=0;
                    logic2=0;
                    logictab2=0;
                    break;

                }
                if ((((j - nowsize)+2) >((g.ws_col)-m))&&(*wrap))
                {
                    nowsize=j+1;
                    logic2=1;
                    m=0;
                    break;
                }
                if (((j+1)>=go->sizeS)&&(!(*wrap)))
                {
                    logictab2=0;
                    break;
                }
                if ((((j - nowsize)+2) >((g.ws_col)-m))&&(!(*wrap)))
                {
                    logictab2=0;
                    break;
                }
            }
        }


        if (((((size-nowsize)<=0||j==go->sizeS))&&(logic2==0))||(!(*wrap)))
        {
            if(go)
            {
                go = go->next;
            }
            if(go!=NULL)

            {
                size = go->sizeS;
            }
            nowstr=nowstr+1;
            if((*wrap))
            {
                nowsize=0;
            }
            if(!(*wrap))
            {
                h=h+1;
                /*   wprintf("\n");*/
            }
            logic=0;
            logic3=0;
        }
        if ((g.ws_row)&&((height % g.ws_row)==0))
        {
            y=L'h';
            while (1)
            {

                if(isatty(0))
                {
                    y = mygetch();
                }
                else
                {
                    y=fgetwc(stdin);
                }
                if (y==WEOF)

                {
                    return OK_EXIT;
                }
                if (y==L'q')
                {

                    wprintf(L"\n");
                    return OK;
                }
                if (y==L' ')
                {


                    len =(go);
                    for (e=0; e<g.ws_row; e++)
                    {
                        if ((e>h-g.ws_row))
                        {
                            if(!len)
                            {
                                break;
                            }
                            if (len->sizeS>maxlength)
                            {
                                maxlength=len->sizeS;
                            }
                        }
                        if(len) len=len->next;
                    }

                    break;
                }
                if(*numbers)
                {
                    k=h;
                    n=1;
                    while (k!=0)
                    {
                        n=n+1;
                        k=k/10;
                    }

                }
                if (y==27)
                {
                    if(isatty(0))
                    {
                        y = mygetch();
                    }
                    else
                    {
                        y=fgetwc(stdin);
                    }
                    if (y==WEOF)

                    {
                        return OK_EXIT;
                    }
                    if (y==91)
                    {
                        if(isatty(0))
                        {
                            y = mygetch();
                        }
                        else
                        {
                            y=fgetwc(stdin);
                        }
                        if (y==WEOF)

                        {
                            return OK_EXIT;
                        }
                        if (((y) == L'C') && (!(*wrap)) && (nowsize <= n + maxlength - g.ws_col))
                        {
                            u = 0;
                            go = (*Begin);
                            fix = nowstr;
                            nowstr = 0;
                            h = 1;
                            for (u = 0; u < fix - g.ws_row; u++)
                            {
                                h = h + 1;
                                nowstr = nowstr + 1;
                                if (go)
                                {
                                    go = go->next;
                                }
                            }
                            nowsize = nowsize + 1;
                            break;
                        }
                        if (((y == L'D') && (!(*wrap)) && (nowsize > 0)))
                        {
                            h = 1;
                            fix = nowstr;
                            nowstr = 0;
                            u = 0;
                            go = (*Begin);
                            for (u = 0; u < fix - g.ws_row; u++)
                            {
                                h = h + 1;
                                nowstr = nowstr + 1;
                                if (go) go = go->next;
                            }

                            nowsize = nowsize - 1;
                            break;
                        }
                    }
                    else
                    {
                        if (y==WEOF)
                        {
                            return OK_EXIT;
                        }
                    }
                }
            }

        }

        {
            wprintf(L"\n");
        }
        height=height+1;


    }

    m=0;

    return OK;
}





/*
 *                        print_range
 *              Функция, которая получает два значения и вызывает print_pages для печати строк из данного диапазона
 *        Возвращает код, с которым завршилась данная программа
 *     На вход принимает
 * struct stroki** Begin                      Указывает на начало списка, в котором хранится текст. Begin->next указывает на первую строку
 * int* numbers                               Указатель на переменную, которая говорит, включен ли вывод номеров строк
 * int* wrap                                  Указатель на переменную, которая говорит, включено ли обрезание строк
 * int* tab                                   Указатель на переменную, в которой хранится число. На это кол-во пробелов заменяется tab
 * int kolSTR                                 Переменная, которая передает кол-во строк в списке
 */



int print_range(struct stroki** Begin,int* numbers,int* wrap,int* tab,int *kolSTR)
{
    wchar_t * loc;
    wint_t input;
    int exit_eof=0;
    int num1=0;
    int num2=0;
    wchar_t* arguments1 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor1;
    int arg_size=1;
    wchar_t x;
    int r;


    int j=-1;
    int logic =0;
    input=fgetwc(stdin);
    if (input==WEOF)
    {
        exit_eof=1;
        x=L'\n';
    }
    else
    {
        x=input;
    }
    while (x==L' ')
    {
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }
    }
    while(zifra(x))
    {
        logic=1;
        j=j+1;
        if(j==arg_size-1)
        {
            loc=realloc(arguments1,2*arg_size*sizeof(wchar_t));
            if (loc==NULL)
            {
                while(x!=L'\n')
                {
                    input=fgetwc(stdin);
                    if (input==WEOF)
                    {
                        exit_eof=1;
                        x=L'\n';
                    }
                    else
                    {
                        x=input;
                    }
                }
                free(arguments1);
                return LOCK;
            }
            else
            {
                arguments1=loc;
            }
            arg_size=arg_size*2;
        }

        arguments1[j]=x;
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }
    }
    if (x == L'#')
    {
        while (x != L'\n')
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                x=L'\n';
            }
            else
            {
                x=input;
            }
        }
    }
    r=0;
    if(logic==1)
    {
        arguments1[j+1]=L'\0';
        cursor1 = arguments1;
        get_int(&cursor1, &r);
        (num1)=r;
    }
    else
    {
        return ERROR_ARG;
    }
    if (x==L' ')
    {

        arg_size=1;
        j=-1;
        logic =0;
        free(arguments1);
        arguments1 =(wchar_t*)malloc(1*sizeof(wchar_t));
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            x=L'\n';
        }
        else
        {
            x=input;
        }
        while (x==L' ')
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                x=L'\n';
            }
            else
            {
                x=input;
            }
        }
        while(zifra(x))
        {
            logic=1;
            j=j+1;
            if(j==arg_size-1)
            {
                loc=realloc(arguments1,2*arg_size*sizeof(wchar_t));
                if (loc==NULL)
                {
                    free(arguments1);
                    return LOCK;
                }
                else
                {
                    arguments1=loc;
                }
                arg_size=arg_size*2;
            }
            arguments1[j]=x;
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                x=L'\n';
            }
            else
            {
                x=input;
            }
        }
        if (x == L'#')
        {
            while (x != L'\n')
            {
                input=fgetwc(stdin);
                if (input==WEOF)
                {
                    exit_eof=1;
                    x=L'\n';
                }
                else
                {
                    x=input;
                }
            }
        }
        r=0;
        if(logic==1)
        {
            arguments1[j+1]=L'\0';
            cursor1 = arguments1;
            get_int(&cursor1, &r);
            num2=r;
            r=print_pages( Begin, numbers, wrap, tab,num1,num2,(*kolSTR));
            free(arguments1);
            if(exit_eof==1)
                return OK_EXIT
            else
                return r;
        }
        else
        {
            free(arguments1);
            return ERROR_ARG;
        }
    }
    else
    {
        if (x==L'\n')
        {
            r=print_pages( Begin, numbers, wrap, tab,num1,(*kolSTR),(*kolSTR));
            return ERROR_ARG;
        }
        else
        {
            free(arguments1);
            return ERROR_ARG;
        }
    }

}
