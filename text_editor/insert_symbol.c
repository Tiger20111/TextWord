#define _POSIX_C_SOURCE 200112L


#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>


#include "insert_symbol.h"
#include "insert_afters.h"

/*
 *             zeta
 *         Зета-функция, которая заполняет массив z(объявлен внутри функции) кол-вом совпадений символов начиная с i символа в i ячейку массива z
 *      Возвращает сам заполненный массив z данными значениями
 *    На вход принимает
 *  wchar* s             массив, в которой хранится сама строка, по которой мы вычисляем зета-функцию
 *  int sizeS            переменная, в которой записана длина строки s
 */

int* zeta(  wchar_t* s, int sizeS )
{
    int* z = (int*)malloc(sizeS*sizeof(int));
    int n=sizeS;
    int i=1,l=0,r=0;
    for (i=0; i<n; i++)
    {
        z[i]=0;
    }
    for( i=1,l=0,r=0; i<n; ++i)
    {
        if (i<=r)
        {
            if(r-i+1<z[i-l])
            {
                z[i]=r-i+1;
            }
            else
            {
                z[i]=z[i-l];
            }
        }
        while((i+z[i]<n)&&((s[z[i]]) == (s[i+z[i]])))
        {
            ++(z[i]);
        }
        if (i+z[i]-1>r)
        {
            l=i;
            r=i+z[i]-1;
        }

    }

    return z;
}


/*
 *                  replace_substring
 *             Функция, которая заменяет одну строку в тексте, который хранится в списке, из какого-то диапазона, на другую строку.
 *        Возвращает код, с которым завершилась данная функция
 *     На вход принимает
 *  struct stroki ** Begin          указатель на  указатель на начало строк. Begin->next указывает на первую строку
 *  struct stroki ** End            указатель на указатель на конец строкю End указывает на последнюю строку.
 *  int* kolSTR                     указатель на переменную в которой хранится кол-во строк в списке в текущий момент
 *
 */


int replace_substring(struct stroki** Begin,struct stroki** End,int* kolSTR)
{
    int logica=0;
    wchar_t* loc;
    wint_t input;
    int exit_eof=0;
    wchar_t* arguments1 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor1;
    wchar_t* arguments2 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor2;
    struct stroki *del;
    struct stroki *begin;
    struct stroki *end;
    wchar_t* line1 =(wchar_t*)malloc(100*sizeof(wchar_t));
    int nowsizeline1=0;
    int maxsizeline1=100;
    wchar_t* line2 =(wchar_t*)malloc(100*sizeof(wchar_t));
    wchar_t* nowline =(wchar_t*)malloc(100*sizeof(wchar_t));

    int z;
    int nowsizeline2=0;
    int maxsizeline2=100;
    int r1=1;
    int r2=(*kolSTR)+2;
    int j=-1;
    int arg_size=1;
    wchar_t x;
    int i;
    wchar_t* line =(wchar_t*)malloc(100*sizeof(wchar_t));
    int sizeSTR=0;
    int k=100;
    int nowsize=0;
    int nowmax=100;
    int u;
    int o;
    int* ze;
    int kol;
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

    line1[0]=L'f';
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
     u=0;
     o=0;
    if (x!=L'"')
    {
        while (zifra(x))
        {
            j = j + 1;
            if (j == arg_size - 1)
            {
                loc = realloc(arguments1, 2 * arg_size * sizeof(wchar_t));
                if(loc==NULL)
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
                    free(arguments2);
                    free(line1);
                    free(line2);
                    free(nowline);
                    free(line);
                    return LOCK;
                }
                else
                {
                    arguments1=loc;
                }
                arg_size = arg_size * 2;
            }
            arguments1[j] = x;
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

        arguments1[j + 1] = L'\0';
        cursor1 = arguments1;
        get_int(&cursor1, &r1);
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
        if (x!=L'"')
        {

            j = -1;
            arg_size = 1;
            while (zifra(x))
            {
                j = j + 1;
                if (j == arg_size - 1)
                {
                    loc = realloc(arguments2, 2 * arg_size * sizeof(wchar_t));
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
                        free(arguments2);
                        free(line1);
                        free(line2);
                        free(nowline);
                        free(line);
                        return LOCK;
                    }
                    else
                    {
                        arguments2=loc;
                    }
                    arg_size = arg_size * 2;
                }
                arguments2[j] = x;
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

            arguments2[j + 1] = L'\0';
            cursor2 = arguments2;
            get_int(&cursor2, &r2);

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
    if(x==L'"')
    {
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            free(arguments1);
            free(arguments2);
            free(line1);
            free(line2);
            free(nowline);
            free(line);
            return ERROR_INPUT;
        }
        else
        {
            x=input;
        }
        while (x != L'"')
        {
            line1[nowsizeline1]=x;
            nowsizeline1++;
            if(nowsizeline1>=maxsizeline1)
            {
                loc = realloc(line1, 2 * maxsizeline1 * sizeof(wchar_t));
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
                    free(arguments2);
                    free(line1);
                    free(line2);
                    free(nowline);
                    free(line);
                    return LOCK;
                }
                else
                {
                    line1=loc;
                }
                maxsizeline1=maxsizeline1*2;
            }
            input=fgetwc(stdin);
            if (input==WEOF)
            {

                free(arguments1);
                free(arguments2);
                free(line1);
                free(line2);
                free(nowline);
                free(line);
                return ERROR_INPUT;
            }
            else
            {
                x=input;
            }

        }
    }
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
   if(x!='\n')
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


    if(x==L'"')
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
        while (x != L'"')
        {
            line2[nowsizeline2]=x;
            nowsizeline2++;
            if(nowsizeline2>=maxsizeline2)
            {
                loc = realloc(line2, 2 * maxsizeline2 * sizeof(wchar_t));
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
                    free(arguments2);
                    free(line1);
                    free(line2);
                    free(nowline);
                    free(line);
                    return LOCK;
                }
                else
                {
                    line2=loc;
                }
                maxsizeline2=maxsizeline2*2;
            }
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

    if (maxsizeline1+1>k)
    {
        loc=realloc(line, 2*k * sizeof(wchar_t));
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
            free(arguments2);
            free(line1);
            free(line2);
            free(nowline);
            free(line);
            return LOCK;
        }
        else
        {
            line=loc;
        }
        k=k*2;
    }

    for(i=0; i < nowsizeline1; i++)
    {
        line[i]=line1[i];
    }

    line[nowsizeline1]=L'|';
    sizeSTR=nowsizeline1+1;






    begin=(*Begin)->next;
    for (i=0; i<r1-1; i++)
    {
        begin=begin->next;
    }

    end=(*Begin);
    for (i=0; i<r2+1; i++)
    {
        if(end) end=end->next;
        else
            end=NULL;
    }


    if(line1[0]==L'$' && nowsizeline1==1)
    {

        while(begin!=end)
        {
             z=100;
            while(z < begin->sizeS)
            {
                z=z*2;
            }
            if (z+nowsizeline2>=z)
            {
                loc = realloc(begin->s, 2 * z * sizeof(wchar_t));
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
                    free(arguments2);
                    free(line1);
                    free(line2);
                    free(nowline);
                    free(line);
                    return LOCK;
                }
                else
                {
                    begin->s=loc;
                }
            }
            for(o=0; o<nowsizeline2; o++)
            {
                begin->s[begin->sizeS]=line2[o];
                begin->sizeS++;
            }
            begin=begin->next;

        }
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
        if(x==L'#')
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
        }
        free(line);
        free(arguments1);
        free(arguments2);
        free(line1);
        free(line2);
        free(nowline);
        if(exit_eof==1)
        {return OK_EXIT;}
        else
            return OK;

    }



    if(line1[0]==L'^' && nowsizeline1==1)
    {

        while(begin!=end)
        {
          z=100;
            while(z < begin->sizeS)
            {
                z=z*2;
            }
            if (z+nowsizeline2>=z)
            {
                loc = realloc(begin->s, 2 * z * sizeof(wchar_t));
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
                    free(arguments2);
                    free(line1);
                    free(line2);
                    free(nowline);
                    free(line);
                    return LOCK;
                }
                else
                {
                    begin->s=loc;
                }

            }

            begin->sizeS+=nowsizeline2;

            for(o=begin->sizeS; o>nowsizeline2; o--)
            {

                begin->s[o]=begin->s[o-nowsizeline2];

            }

            for(o=0; o<nowsizeline2; o++)
            {
                begin->s[o]=line2[o];

            }
            begin=begin->next;

        }
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
        if(x==L'#')
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
        }
        free(line);
        free(arguments1);
        free(arguments2);
        free(line1);
        free(line2);
        free(nowline);
        if(exit_eof==1)
            return OK_EXIT
        else
            return OK;

    }

    while(begin!=end)
    {
        for(i=0; i<=begin->sizeS-1; i++)
        {



            line[sizeSTR]=begin->s[i];
            sizeSTR++;
            if (sizeSTR + 2 > k)
            {
                loc = realloc(line, 2 * k * sizeof(wchar_t));
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
                    free(line);
                    free(arguments1);
                    free(arguments2);
                    free(line1);
                    free(line2);
                    free(nowline);
                    return LOCK;
                }
                else
                {
                    line=loc;
                }
                k=k*2;
            }


        }


        line[sizeSTR]=L'\\';
        sizeSTR++;
        if (sizeSTR + 2 > k)
        {
            loc = realloc(line, 2 * k * sizeof(wchar_t));
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
                free(arguments2);
                free(line1);
                free(line2);
                free(nowline);
                free(line);
                return LOCK;
            }
            else
            {
                line=loc;
            }
            k=k*2;
        }
        line[sizeSTR]=L'n';
        sizeSTR++;

        if (sizeSTR + 2 > k)
        {
            loc = realloc(line, 2 * k * sizeof(wchar_t));
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
                free(arguments2);
                free(line1);
                free(line2);
                free(nowline);
                free(line);
                return LOCK;
            }
            else
            {
                line=loc;
            }
            k=k*2;
        }

        if (begin->prev)
        {
            (begin->prev)->next=begin->next;
            if(begin->next)
            {
                (begin->next)->prev=begin->prev;
            }
        }
        del=begin;
        begin=begin->next;
        free(del->s);
        free(del);
        (*kolSTR)--;


    }

    line[sizeSTR-2]=L'"';
    line[sizeSTR-1]=L'\n';
    line[sizeSTR]=L'\000';








    ze=zeta(line,sizeSTR);



     kol=0;
    for(i=0; i<sizeSTR; i++)
    {
        if (ze[i]==nowsizeline1)
        {
            kol++;
        }
    }




    i=nowsizeline1+1;




    while(i<sizeSTR)
    {
        if(ze[i]!=nowsizeline1)
        {
            nowline[nowsize]=line[i];
            nowsize++;
            if (nowsize + 2 > nowmax)
            {
                loc = realloc(nowline, 2 * nowmax * sizeof(wchar_t));
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
                    free(ze);
                    free(arguments1);
                    free(arguments2);
                    free(line1);
                    free(line2);
                    free(nowline);
                    free(line);
                    return LOCK;
                }
                else
                {
                    nowline=loc;
                }
                nowmax=nowmax*2;
            }
        }
        else
        {
            for (u=0; u<nowsizeline2; u++)
            {
                nowline[nowsize] = line2[u];
                nowsize++;
                if (nowsize + 2 > nowmax)
                {
                    loc = realloc(nowline, 2 * nowmax * sizeof(wchar_t));
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
                        free(ze);
                        free(arguments1);
                        free(arguments2);
                        free(line1);
                        free(line2);
                        free(nowline);
                        free(line);
                        return LOCK;
                    }
                    else
                    {
                        nowline=loc;
                    }
                    nowmax = nowmax * 2;
                }


            }
            i=i+nowsizeline1-1;
        }
        i++;
    }

    nowline[nowsize]=L'"';
    if (nowsize + 2 > nowmax)
    {
        loc = realloc(nowline, 2 * nowmax * sizeof(wchar_t));
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
            free(ze);
            free(arguments1);
            free(arguments2);
            free(line1);
            free(line2);
            free(nowline);
            free(line);
            return LOCK;
        }
        else
        {
            nowline=loc;
        }
        nowmax=nowmax*2;
    }
    nowline[nowsize]=L'\n';
    if (nowsize + 2 > nowmax)
    {
        loc = realloc(nowline, 2 * nowmax * sizeof(wchar_t));
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
            free(ze);
            free(arguments1);
            free(arguments2);
            free(line1);
            free(line2);
            free(nowline);
            free(line);
            return LOCK;
        }
        else
        {
            nowline=loc;
        }
        nowmax=nowmax*2;
    }
    nowline[nowsize]='\000';
    if ((*Begin)->next==NULL)
    {

        (*End)=(*Begin);
        (*End)->next=NULL;


    }
if ((*kolSTR)==0)
{
    (*kolSTR)--;
    logica=1;
}
    insert_after(Begin,End,kolSTR,1,nowline,r1-1);
if(logica==1)
{
    (*kolSTR)++;
}
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
    if(x=='#')
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
    }
    free(ze);
    free(line);
    free(arguments1);
    free(arguments2);
    free(line1);
    free(line2);
    free(nowline);
    if(exit_eof==0)
    {return OK;}
    else
        return OK_EXIT;

}


/*               edit_string
 *          Функция, которая заменяет в x строке на y позиции символ, на который нам передали(или вставляет в x строку на y позицию символ, который нам передали). В зависимости от флага f.
 *       Возвращает код, с которым завершилась данная функция
 *  struct stroki ** Begin          указатель на  указатель на начало строк. Begin->next указывает на первую строку
 *  struct stroki ** End            указатель на указатель на конец строкю End указывает на последнюю строку.
 *  int* kolSTR                     указатель на переменную в которой хранится кол-во строк в списке в текущий момент
 *  int f                           флаг, который определяет, вызывали ли мы edit_string или insert_symbol. Если f==1, то вызвали insert_symbol иначе edit_string
 */


int edit_string(struct stroki** Begin,struct stroki** End,int* kolSTR,int f)
{
    int logic1=0;
    wchar_t * loc;
    struct stroki* NewElement;
    wchar_t* arguments1 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor1;
    wchar_t* arguments2 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor2;
    wchar_t* line;
    struct stroki * go;
    int symbol;
    int e=1;
    int a;
    int logic=0;
    int spec_symbol;
    wchar_t x;
    int z;
    int r1;
    int r2;
    int j=-1;
    int i;
    int k;
    int arg_size=1;
    int h;
    wint_t input;
    int exit_eof=0;
    int sizeSTR;
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
    while (zifra(x))
    {
        logic1=1;
        j = j + 1;
        if (j == arg_size-1)
        {
            loc = realloc(arguments1, 2 * arg_size * sizeof(wchar_t));
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
                free(arguments2);
                return LOCK;
            }
            else
            {
                arguments1=loc;
            }
            arg_size = arg_size * 2;
        }
        arguments1[j] = x;
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
    if (logic1==1)
    {
        arguments1[j + 1] = L'\0';
        cursor1 = arguments1;
        get_int(&cursor1, &r1);
        logic1=0;
    }
    else
    {
        free(arguments1);
        free(arguments2);
        return ERROR_ARG;
    }
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
    arg_size=1;
    while (zifra(x))
    {
        logic1=1;
        j = j + 1;
        if (j == arg_size-1)
        {
            loc = realloc(arguments2, 2 * arg_size * sizeof(wchar_t));
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
                free(arguments2);
                return LOCK;
            }
            else
            {
                arguments2=loc;
            }
            arg_size = arg_size * 2;
        }
        arguments2[j] = x;
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
    if (logic1)
    {
        arguments2[j + 1] = L'\0';
        cursor2 = arguments2;
        get_int(&cursor2, &r2);
    }
    else
    {
        free(arguments1);
        free(arguments2);
        return ERROR_ARG;
    }
    r2=r2-1;

    if(r1>(*kolSTR))
    {
        free(arguments1);
        free(arguments2);
        return ERROR_INPUT;
    }

    go=(*Begin)->next;
    for (i=0; i<r1-1; i++)
    {
        go=go->next;
    }
    input=fgetwc(stdin);
    if (input==WEOF)
    {
        exit_eof=1;
        symbol=L'\n';
    }
    else
    {
        symbol=input;
    }
    while (symbol==L' ')
    {
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            symbol=L'\n';
        }
        else
        {
            symbol=input;
        }
    }
    input=fgetwc(stdin);
    if (input==WEOF)
    {
        exit_eof=1;
        spec_symbol=L'\n';
    }
    else
    {
        spec_symbol=input;
    }
    while (spec_symbol==L' ')
    {
        input=fgetwc(stdin);
        if (input==WEOF)
        {
            exit_eof=1;
            spec_symbol=L'\n';
        }
        else
        {
            spec_symbol=input;
        }
    }
    if(spec_symbol==L'#')
    {
        while(spec_symbol!=L'\n')
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                spec_symbol=L'\n';
            }
            else
            {
                spec_symbol=input;
            }
        }
    }

    if (spec_symbol!=L'\n')
    {
        if ((symbol==L'\\')&&(spec_symbol == L'n'))
        {
            symbol=L'\n';
        }
        if ((symbol==L'\\')&&(spec_symbol == L'r'))
        {
            symbol=L'\r';
        }
        if ((symbol==L'\\')&&(spec_symbol == L'"'))
        {
            symbol=L'"';
        }

        if ((symbol==L'\\')&&(spec_symbol == L't'))
        {
            symbol=L'\t';
        }
    }
    if(symbol!=L'\n')
    {
        if(!f)
        {
            if ((r2>=0)&&(r2<=go->sizeS))
            {
                go->s[r2]=symbol;
            }
            else
            {
                free(arguments1);
                free(arguments2);
                wprintf(L"Leaving the border\n");
                return OK;
            }
        }
        else
        {
            if ((r1<=0)||(r1>(*kolSTR)))
            {
                free(arguments1);
                free(arguments2);
                wprintf(L"Leaving the border\n");
                return OK;
            }

            if(r2<=0)
            {
                r2=0;
            }
            if(r2>=(go->sizeS))
            {
                r2=go->sizeS;
            }
            logic=0;
             z=go->sizeS-1;
            z++;
            if (z%100==0)
            {
                z=z/100;
                h=z;
                e=1;
                while (h!=0)
                {
                    h=h>>1;
                    e=e*2;
                }
                if (2*z==e)
                {
                    logic=1;
                }
            }
            e=e*100;
            if (logic==1)
            {
                loc = realloc(go->s, e * sizeof(wchar_t));
                if(loc==NULL)
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
                    free(arguments2);
                    return LOCK;
                }
                else
                {
                    go->s=loc;
                }
            }


            for (a=go->sizeS+1; a>r2; a--)
            {
                go->s[a]=go->s[a-1];
            }
            go->s[r2]=symbol;
            go->sizeS++;
        }

    }
    else
    {

        sizeSTR=0;
        line  = NULL;
        line =(wchar_t*)malloc(100*sizeof(wchar_t));
        k=100;
        for(i=r2+1-f; i<=(go->sizeS); i++)
        {
            line[sizeSTR]=go->s[i];
            sizeSTR++;
            if (sizeSTR + 2 > k)
            {
                loc = realloc(line, 2 * k * sizeof(wchar_t));
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
                    free(arguments2);
                    return LOCK;
                }
                else
                {
                    line=loc;
                }
                k = k * 2;
            }
        }
        go->sizeS=r2;
        go->s[r2]=L'\000';

        NewElement = (struct stroki *)malloc(1* sizeof(struct stroki));
        NewElement->next = go->next;
        NewElement->prev = go;
        if(go->next!=NULL)
        {
            (go->next)->prev=NewElement;
        }
        go->next=NewElement;
        NewElement->s=line;
        NewElement->sizeS=sizeSTR-1;
        if(r1==(*kolSTR))
        {
            (*End)=NewElement;
            if (*End)  (*End)->next=NULL;
        }
        if(spec_symbol!=L'\n')
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
        }

        (*kolSTR)++;
    }

    free(arguments1);
    free(arguments2);
    if(exit_eof)
        return OK_EXIT
    else
        return OK;
}

/*
 *                delete_braces
 *          Функция, которая принимает диапазон и из данного диапазона удаляет все содеримое между '{' и '}'
 *      Возвращает код, с которым завершилась даннная функция
 *    На вход принимает
 *  struct stroki ** Begin            указатель на  указатель на начало строк. Begin->next указывает на первую строку
 *  struct stroki ** End              указатель на указатель на конец строкю End указывает на последнюю строку.
 *  int* kolSTR                       указатель на переменную в которой хранится кол-во строк в списке в текущий момент
 *  int f                             флаг, который говорит, будет ли диапазон или нужно удалять во всем тексте
 */

int delete_braces(struct stroki** Begin,struct stroki** End,int* kolSTR,int f)
{
    wchar_t* arguments1 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor1;
    wchar_t* arguments2 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor2;
    wchar_t* line =(wchar_t*)malloc(100*sizeof(wchar_t));
    wchar_t* loc;
    int k=100;
    int sizeSTR=0;
    int r1;
    int r2;
    int j=-1;
    int i;
    wint_t input;
    int exit_eof=0;
    int arg_size=1;
    wchar_t x;
    int balance=0;
    int logic=0;
    struct stroki *del;
    struct stroki *begin=NULL;
    struct stroki *end;
    struct stroki NowHelp;
if((*kolSTR)==0)
{
    free(arguments1);
    free(arguments2);
    free(line);
    return OK;
}

    if (f==1)
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
        while (x == L' ')
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
        while (zifra(x))
        {
            j = j + 1;
            if (j == arg_size - 1)
            {
                loc = realloc(arguments1, 2 * arg_size * sizeof(wchar_t));
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
                    free(arguments2);
                    free(line);
                    return LOCK;
                }
                else
                {
                    arguments1=loc;
                }
                arg_size = arg_size * 2;
            }
            arguments1[j] = x;
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

        arguments1[j+1] = L'\0';
        cursor1 = arguments1;
        get_int(&cursor1, &r1);

        if (x == L' ')
        {
            while (x == L' ')
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

            j = -1;
            arg_size = 1;
            while (zifra(x))
            {
                j = j + 1;
                if (j == arg_size - 1)
                {
                    loc = realloc(arguments2, 2 * arg_size * sizeof(wchar_t));
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
                        free(arguments2);
                        free(line);
                        return LOCK;
                    }
                    else
                    {
                        arguments2=NULL;
                    }
                    arg_size = arg_size * 2;
                }
                arguments2[j] = x;
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

            arguments2[j + 1] = L'\0';
            cursor2 = arguments2;
            get_int(&cursor2, &r2);

        }
        else
        {
            r2=(*kolSTR);
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
        }


    }
    else
    {
        r1=1;
        r2=(*kolSTR);
    }

    if((r2==(*kolSTR)))
    {
        r1=1;
        logic=1;
        begin=(*Begin)->next;
        end=(*End)->next;
    }
    else
    {
        begin=(*Begin);
        for (i=0; i<r1; i++)
        {
            begin=begin->next;
        }
        end=(*Begin);
        for (i=0; i<r2+1; i++)
        {
            if(end) end=end->next;
        }
    }
    if (r2==(*kolSTR))
    {
        (*End)=end;
        if (*End)  (*End)->next=NULL;
    }


    while(begin!=end)
    {

        for(i=0; i<=begin->sizeS-1; i++)
        {
            if ((begin->s[i]==L'{'))
            {
                if (begin->s[i]==L'{') balance++;

            }
            else
            {
                if ((begin->s[i]==L'}')&&(balance>0))
                {
                    balance --;
                    continue;
                }

                if (balance==0)
                {
                    line[sizeSTR]=begin->s[i];
                    sizeSTR++;
                    if (sizeSTR + 2 > k)
                    {
                        loc = realloc(line, 2 * k * sizeof(wchar_t));
                        if (loc==NULL)
                        {
                            free(arguments1);
                            free(arguments2);
                            free(line);
                            return LOCK;
                        }
                        else
                        {
                            line=loc;
                        }
                        k=k*2;
                    }

                }
            }

        }

        if ((balance==0))
        {
            if(begin )
            {

                if((begin->sizeS>0) &&(begin->s[begin->sizeS-1]!=L'}'))
                {

                    line[sizeSTR] = L'\\';
                    sizeSTR++;
                    if (sizeSTR + 2 > k)
                    {
                        loc = realloc(line, 2 * k * sizeof(wchar_t));
                        if (loc==NULL)
                        {
                            free(arguments1);
                            free(arguments2);
                            free(line);
                            return LOCK;
                        }
                        else
                        {
                            line=loc;
                        }
                        k = k * 2;
                    }
                    line[sizeSTR] = L'n';
                    sizeSTR++;
                    if (sizeSTR + 2 > k)
                    {
                        loc = realloc(line, 2 * k * sizeof(wchar_t));
                        if (loc==NULL)
                        {
                            free(arguments1);
                            free(arguments2);
                            free(line);
                            return LOCK;
                        }
                        else
                        {
                            line=loc;
                        }
                        k = k * 2;
                    }
                    (*kolSTR)++;
                }
            }

        }
        if (begin )
        {
                (begin->prev)->next=begin->next;


                if (begin->next) {
                    (begin->next)->prev = begin->prev;
                }

        }



        (*kolSTR)--;



        del=begin;
        if(begin) begin=begin->next;
        if (del == (*End))
        {
            if((*End)->prev)
            {
                (*End)=(*End)->prev;
            }
        }
        if(del) free(del->s);

        if(del)free(del);
    }

    if(balance!=0)
    {
        if (sizeSTR >= k)
        {
            loc = realloc(line, 2 * k * sizeof(wchar_t));
            if (loc==NULL)
            {
                free(arguments1);
                free(arguments2);
                free(line);
                return LOCK;
            }
            else
            {
                line=loc;
            }
            k = k * 2;
        }
        line[sizeSTR] = L'"';
        sizeSTR++;
        if (sizeSTR  >= k)
        {
            loc = realloc(line, 2 * k * sizeof(wchar_t));
            if (loc==NULL)
            {
                free(arguments1);
                free(arguments2);
                free(line);
                return LOCK;
            }
            else
            {
                line=loc;
            }
            k = k * 2;
        }
        line[sizeSTR] = L'\n';
        sizeSTR++;
        if (sizeSTR  >= k)
        {
            loc = realloc(line, 2 * k * sizeof(wchar_t));
            if (loc==NULL)
            {
                free(arguments1);
                free(arguments2);
                free(line);
                return LOCK;
            }
            else
            {
                line=loc;
            }
            k = k * 2;
        }
        line[sizeSTR ] =L'\0';
        (*kolSTR)--;
    }
    else
    {


        line[sizeSTR-2]=L'"';
        if (sizeSTR  >= k)
        {
            loc = realloc(line, 2 * k * sizeof(wchar_t));
            if (loc==NULL)
            {
                free(arguments1);
                free(arguments2);
                free(line);
                return LOCK;
            }
            else
            {
                line=loc;
            }
            k = k * 2;
        }
        line[sizeSTR-1]=L'\n';

        line[sizeSTR]=L'\0';
        sizeSTR++;
    }
    if ((r1==1)&&(logic==0))
    {
        (*Begin)->next=begin;
    }

    if ((*Begin)->next==NULL)
    {

        (*Begin)->next=&NowHelp;
        if (*End) (*End)=&NowHelp;
        ((*Begin)->next)->next=(*End);
        if (*End) (*End)->prev=(*Begin);
        if (*End)  (*End)->next=NULL;
    }

    r1--;
    if((*End)==NULL)
    {
        r1=-1;
        (*End)=(*Begin);
        (*End)->prev=(*Begin);
    }

    if(line[0]!=L'"'||line[1]!=L'\n')    insert_after(Begin,End,kolSTR,1,line,r1);


    free(arguments1);
    free(arguments2);
    free(line);
    if(exit_eof==1)
        return OK_EXIT
    else
        return OK;

}
