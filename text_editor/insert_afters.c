#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "alllib.h"


/*
 *                              insert_after
 *                       Функция, которая вставляет полученный внутри функции строку или группу строк или переданную в функцию через функцию через массив string
 *            Возвращает код, с которым завершилась данная функция.
 *       На вход принимает
 * struct stroki ** Begin                        указатель на  указатель на начало строк. Begin->next указывает на первую строку
 * struct stroki ** End                          указатель на указатель на конец строкю End указывает на последнюю строку.
 * int* kolSTR                                   указатель на переменную в которой хранится кол-во строк в списке в текущий момент
 * int z                                         передан флаг через эту переменную, который сообщает передали ли мы строку через массив или через поток ввода. z==1 через массив
 * wchar_t* string                               массив, в котором хранится переданная строка для вставки(если была передана)
 * int nom                                       номер строки, после которой нужно вставить(если было передана строка через файл)
 */

int insert_after(struct stroki** Begin,struct stroki** End,int* kolSTR,int z,wchar_t *string,int nom)
{
    wint_t input;
    int exit_eof=0;
    wchar_t now=L' ';
    wchar_t next=L' ';
    wchar_t control_=L' ';
    int logic6=0;
    int m=0;
    struct stroki *NewElement = NULL;
    struct stroki *NewElement1 = NULL;
    wchar_t* line  = NULL;
    struct stroki* go =NULL;
    wchar_t rev[3];
    int r = 0;
    wchar_t* arguments1=NULL, *cursor1=NULL;
    int arg_size=1;
    wint_t x=L'\0';
    int logic = 0;
    int j=0;
    int sizeSTR=0;
    int k=0;
    int w=0;
    struct stroki* first=NULL;
    struct stroki* second=NULL;
    wchar_t* loc;

    wchar_t vvod[3];
    vvod[0]=L'\0';
    vvod[1]=L'\0';
    vvod[2]=L'\0';
     rev[0]=L'\0';
    rev[1]=L'\0';
    rev[2]=L'\0';
    if (z==0)
    {
        arguments1 =(wchar_t*)malloc(1*sizeof(wchar_t));
        x=fgetwc(stdin);
        while (x==L' ')
        {
            x=fgetwc(stdin);
        }
        j = -1;
        while (zifra(x))
        {
            logic = 1;

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
                    return LOCK;
                }
                else
                {
                    arguments1=loc;
                }
                arg_size = arg_size * 2;
            }
            arguments1[j] = x;
            x=fgetwc(stdin);

        }


        if (logic == 1)
        {
            arguments1[j + 1] = L'\0';
            cursor1 = arguments1;
            get_int(&cursor1, &r);
            if ((r > (*kolSTR)))
            {
                r=(*kolSTR);
            }
        }
        else
        {
            r = (*kolSTR);
            logic=0;
        }
        free(arguments1);
    }
    else
    {
        r=nom;
        x=L'"';
    }


    if(logic==1)
    {
        if (z == 0) x=fgetwc(stdin);
        while (x == L' ')
        {
            x=fgetwc(stdin);
        }
    }
    if(x!=L'"')
    {
        while (x != L'\n')
        {
            x=fgetwc(stdin);
        }

        return ERROR_ARG;
    }
    else
    {
        if (z==0)
        {
            wint_t symb;
            symb=fgetwc(stdin);
            /*XXX
             * Здесь обязательно нужно проверить
             * на WEOF!!!!0v51-`    1
             *
             * Обязательно перед присвоением,
             * если этого не сделать будет ошибка,
             * невозможно будет распознать конец
             * файла после присвоения.
             *
             * Всюду ниже править тоже.
             */
            rev[0]=symb;
        }
        if (z==1)
        {
            rev[0]=string[m];
            m++;
        }
        if (z==0)
        {
            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                rev[1]=L'\n';
            }
            else
            {
                rev[1]=input;
            }
        }
        if (z==1)
        {
            rev[1]=string[m];
            m++;
        }
        if((rev[0]==L'"') && (rev[1]==L'"') )
        {

            sizeSTR=0;

            NewElement1 = calloc(1, sizeof(struct stroki));
            first=NewElement1;
            second=NewElement1;
            input=fgetwc(stdin);
            if (input==WEOF)
            {
              free(NewElement1);
                return ERROR_INPUT;
            }
            else
            {
                vvod[0]=input;
            }

            input=fgetwc(stdin);
            if (input==WEOF)
            {
                free(NewElement1);
                return ERROR_INPUT;
            }
            else
            {
                vvod[1]=input;
            }

            input=fgetwc(stdin);
            if (input==WEOF)
            {
                free(NewElement1);
                return ERROR_INPUT;
            }
            else
            {
                vvod[2]=input;
            }

            line =(wchar_t*)malloc(100*sizeof(wchar_t));
            k=100;

            while((vvod[0]!=L'"')||(vvod[1]!=L'"')||(vvod[2]!=L'"'))
            {
                if(vvod[0]!=L'\n')
                {
                    line[sizeSTR] = vvod[0];
                    sizeSTR++;
                }
                else
                {

                    (*kolSTR)++;
                    NewElement = calloc(1, sizeof(struct stroki));
                    NewElement->prev=NULL;
                    NewElement->next=NULL;
                    NewElement->s = line;
                    NewElement->prev = (second);
                    NewElement->sizeS=sizeSTR;
                    (second)->next=NewElement;
                    second=NewElement;

                    line =(wchar_t*)malloc(100*sizeof(wchar_t));
                    k=100;
                    sizeSTR=0;
                }

                if (sizeSTR+2>k)
                {
                    /*XXX
                     * Небезопасное использование realloc!!!
                     *
                     */
                    loc=realloc(line,k*2*sizeof(wchar_t));
                    if(loc==NULL)
                    {
                        x=L'\0';
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
                        return LOCK;
                    }
                    else
                    {
                        line=loc;
                    }
                    k=k*2;
                }

                vvod[0]=vvod[1];
                vvod[1]=vvod[2];
                input=fgetwc(stdin);
                if (input==WEOF)
                {
                    free(line);
                    free(NewElement1);
                    return ERROR_INPUT;
                }
                else
                {
                    vvod[2]=input;
                }

            }

            (*kolSTR)++;

            input=fgetwc(stdin);
            if (input==WEOF)
            {
                exit_eof=1;
                vvod[0]='\n';
            }
            else
            {
                vvod[0]=input;
            }

            NewElement = malloc(1* sizeof(struct stroki));
            NewElement->s = line;
            NewElement->prev = (second);
            NewElement->sizeS=sizeSTR;
            (second)->next=NewElement;
            second=NewElement;



            w=0;

            go = *Begin;

            if (r!=-1)
            {
                for (w = 0; w < r; w++)
                {
                    go = go->next;
                }
            }
            else
            {
                go=(*End);
            }
            second->next=go->next;
            (first->next)->prev=go;
            if(go->next!=NULL)
            {
                (go->next)->prev=second;
            }
            else
            {
                (*End)=second;
                (*End)->next=NULL;
            }
            go->next=(first->next);
            if((r==(*kolSTR))||(r==-1))
            {
                (*End)=second;
                if (*End)  (*End)->next=NULL;
            }
            free(first);

        }
        else
        {
            sizeSTR=0;
            line =(wchar_t*)malloc(100*sizeof(wchar_t));
            k=100;
            if ((rev[0]==L'"') && (rev[1]==L'\n'))
            {

                line[0]=L'\0';
                sizeSTR=0;
            }

            else
            {

                sizeSTR=0;
                now=L' ';
                next=L' ';
                control_=L' ';
                if((rev[0]!=L'\\')||(rev[1]!=L'n'))
                {
                    line[0]=rev[0];
                    sizeSTR=1;
                    now=rev[1];
                }
                else
                {
                    now=L'\\';
                    next=L'n';
                }





                if ((rev[0]!=L'"')||((now!=L'\n')))
                {

                    /*     line[1]=rev[1];*/
                    /*   sizeSTR++;*/
                    if(now!=L'\\' || next!=L'n')
                    {
                        if (z == 0)
                        {
                            input=fgetwc(stdin);
                            if (input==WEOF)
                            {
                                exit_eof=1;
                                next=L'\n';
                            }
                            else
                            {
                                next=input;
                            }
                        }

                        if (z == 1)
                        {
                            next = string[m];
                            m++;
                        }
                    }

                    while ((now !=L'"') || (next != L'\n'))
                    {
                        /*  wprintf(L"now: %lc next: %lc\n", now, next);*/
                        if((control_ == L'\\') && (now == L'\\') && ((next ==L'n')||(next==L'r')||(next==L't')))
                        {
                            now=next;
                            if(z==0)
                            {
                                input=fgetwc(stdin);
                                if (input==WEOF)
                                {
                                    exit_eof=1;
                                    next=L'\n';
                                }
                                else
                                {
                                    next=input;
                                }
                            }
                            if (z==1)
                            {
                                next=string[m];
                                m++;
                            }
                        }
                        else
                        {

                            while((control_ != L'\\') && (now == L'\\') && ((next ==L'n')||(next==L'r')||(next==L't')||(next==L'"')))
                            {


                                if (next==L'r')
                                {

                                    control_ = L'\0';
                                    now=L'\r';
                                    if(z==0)
                                    {
                                        input=fgetwc(stdin);
                                        if (input==WEOF)
                                        {
                                            exit_eof=1;
                                            next=L'\n';
                                        }
                                        else
                                        {
                                            next=input;
                                        }
                                    }
                                    if (z==1)
                                    {
                                        next=string[m];
                                        m++;
                                    }

                                }
                                if (next==L't')
                                {

                                    control_ = L'\0';
                                    now=L'\t';
                                    if (z==0)
                                    {
                                        input=fgetwc(stdin);
                                        if (input==WEOF)
                                        {
                                            exit_eof=1;
                                            next=L'\n';
                                        }
                                        else
                                        {
                                            next=input;
                                        }
                                    }
                                    if (z==1)
                                    {
                                        next=string[m];
                                        m++;
                                    }

                                }

                                if (next==L'"')
                                {

                                    control_='\0';
                                    now=L'"';
                                    if (z==0)
                                    {
                                        input=fgetwc(stdin);
                                        if (input==WEOF)
                                        {
                                            exit_eof=1;
                                            next=L'\n';
                                        }
                                        else
                                        {
                                            next=input;
                                        }
                                    }
                                    if (z==1)
                                    {
                                        next=string[m];
                                        m++;
                                    }

                                }

                                if (next==L'n')
                                {
                                    if (r==-1)
                                    {
                                        (*kolSTR)++;
                                        NewElement = malloc(1* sizeof(struct stroki));
                                        NewElement->next = NULL;
                                        NewElement->prev = (*End);
                                        if(*End)
                                        {
                                            (*End)->next = NewElement;
                                            (*End) = NewElement;
                                        }
                                        else
                                        {
                                            (*End) = NewElement;
                                            (*End)->next=NULL;
                                        }
                                        (*End)->s = line;
                                        (*End)->sizeS = sizeSTR;
                                        if (*End)  (*End)->next=NULL;

                                    }
                                    else
                                    {


                                        w=0;
                                        go = *Begin;
                                        for(w=0; w<r; w++)
                                        {
                                            go=go->next;
                                        }


                                        NewElement = malloc(1* sizeof(struct stroki));
                                        NewElement->next = go->next;
                                        NewElement->prev = go;
                                        NewElement->s=line;
                                        NewElement->sizeS=sizeSTR;

                                        if(go->next!=NULL)
                                        {
                                            (go->next)->prev=NewElement;
                                        }

                                        if ((go->next==NULL)&&(z==1))
                                        {
                                            (*End)=NewElement;
                                            if (*End)  (*End)->next=NULL;
                                        }

                                        go->next=NewElement;



                                        if(r==(*kolSTR))
                                        {
                                            (*End)=NewElement;

                                        }
                                        if (*End)  (*End)->next=NULL;
                                        (*kolSTR)++;
                                        r=r+1;

                                    }

                                    line=NULL;
                                    line =(wchar_t*)malloc(100*sizeof(wchar_t));
                                    k = 100;
                                    sizeSTR=0;
                                    control_='\0';
                                    if(z==0)
                                    {
                                        input=fgetwc(stdin);
                                        if (input==WEOF)
                                        {
                                            exit_eof=1;
                                            now=L'\n';
                                        }
                                        else
                                        {
                                            now=input;
                                        }
                                    }
                                    if (z==1)
                                    {
                                        now=string[m];
                                        m++;
                                    }
                                    if (z==0)
                                    {
                                        input=fgetwc(stdin);
                                        if (input==WEOF)
                                        {
                                            exit_eof=1;
                                            next=L'\n';
                                        }
                                        else
                                        {
                                            next=input;
                                        }
                                    }
                                    if (z==1)
                                    {
                                        next=string[m];
                                        m++;
                                    }
                                    logic6=1;

                                }

                            }


                        }

                        if(logic6==1)
                        {
                            logic6=0;
                            continue;
                        }

                        /*wprintf(L"%d %d\n",sizeSTR, k);*/

                        line[sizeSTR] = now;
                        /*wprintf(L"%d %d\n",sizeSTR, k);*/

                        sizeSTR++;
                        control_=now;
                        now = next;
                        if (z==0)
                        {
                            input=fgetwc(stdin);
                            if (input==WEOF)
                            {
                                exit_eof=1;
                                next=L'\n';
                            }
                            else
                            {
                                next=input;
                            }
                        }
                        if (z==1)
                        {
                            next=string[m];
                            m++;
                        }
                        if (sizeSTR + 2 > k)
                        {
                            loc = realloc(line, 2 * k * sizeof(wchar_t));
                            if(loc==NULL)
                            {
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


            if (r==-1)
            {
                (*kolSTR)++;
                NewElement = malloc(1* sizeof(struct stroki));
                NewElement->next = NULL;
                NewElement->prev = (*End);
                (*End)->next = NewElement;
                (*End) = NewElement;
                (*End)->s = line;
                (*End)->sizeS = sizeSTR;
                if (*End)  (*End)->next=NULL;

            }
            else
            {
                w=0;

                go = *Begin;
                for(w=0; w<r; w++)
                {
                    go=go->next;
                }
                (*kolSTR)++;
                NewElement = (struct stroki *)malloc(1* sizeof(struct stroki));
                NewElement->next = go->next;
                NewElement->prev = go;
                if(go->next!=NULL)
                {
                    (go->next)->prev=NewElement;
                }
                if (go)
                {
                    go->next=NewElement;
                }
                go->next=NewElement;
                NewElement->s=line;
                NewElement->sizeS=sizeSTR;
                if(r==(*kolSTR))
                {
                    (*End)=NewElement;

                }
                if (*End)  (*End)->next=NULL;

            }

        }
    }

   if(exit_eof==1)
       return OK_EXIT
    else
       return OK;
}


/*
 *                  delete_range
 *               Функция которая удаляет строки из полученного через ввод в ней диапазона
 *          Возвращает код, с которым завершилась функция
 *      На вход принимает
 * struct stroki ** Begin                        указатель на  указатель на начало строк. Begin->next указывает на первую строку
 * struct stroki ** End                          указатель на указатель на конец строкю End указывает на последнюю строку.
 * int* kolSTR                                   указатель на переменную в которой хранится кол-во строк в списке в текущий момент
 */


int delete_range(struct stroki** Begin,struct stroki** End,int* kolSTR)
{
    int w=0;
    int j=-1;
    wint_t x;
    int logic=0;
    wchar_t* loc;
    wint_t input;
    int exit_eof=0;
    wchar_t* arguments1 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor1;
    wchar_t* arguments2 =(wchar_t*)malloc(1*sizeof(wchar_t)),*cursor2;
    struct stroki* go=NULL;
    struct stroki* del=NULL;

    int r1;
    int r2;
    int arg_size=1;

    x=fgetwc(stdin);

    while (x==L' ')
    {
        x=fgetwc(stdin);
    }
    if (x==L'#')
    {
        while (x!=L'\n')
        {
            x=fgetwc(stdin);
        }
    }
    while (zifra(x))
    {
        logic=1;
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
        if (logic!=1)
        {
         free(arguments1);
         free(arguments2);
            return ERROR_ARG;
        }

        arguments1[j] = x;
        x=fgetwc(stdin);

    }
    if (x==L'#')
    {
        while (x!='\n')
        {
            x=fgetwc(stdin);
        }
    }
    arguments1[j + 1] = L'\0';
    cursor1 = arguments1;

    get_int(&cursor1, &r1);

    arg_size=1;

    if (x!=L'\n' && x!=L'#')
    {
        j=-1;
        x=fgetwc(stdin);
        while (x==L' ')
        {
            x=fgetwc(stdin);
        }
        while (zifra(x))
        {
            j = j + 1;
            if (j == arg_size-1)
            {
                loc = realloc(arguments2, 2 * arg_size * sizeof(wchar_t));
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
                    arguments2=loc;
                }
                arg_size = arg_size * 2;
            }
            arguments2[j] = x;
            x=fgetwc(stdin);

        }
        arguments2[j + 1] = L'\0';
        cursor2 = arguments2;

        get_int(&cursor2, &r2);
    }
    else
    {
        if (x==L'#')
        {
            while (x!=L'\n')
            {
                x=fgetwc(stdin);
            }
        }
        r2=(*kolSTR);
    }
    if (x==L'#')
    {
        while (x!=L'\n')
        {
            x=fgetwc(stdin);
        }
    }
    if ((x!=L'\n'))
    {
        free (arguments1);
        free (arguments2);
        return ERROR_ARG;
    }

    if(r1<=0)
    {
        r1=1;
    }
    if(r2>=(*kolSTR))
    {
        r2=(*kolSTR);
    }

    go = (*Begin);
    for(w=0; w<r1-1; w++)
    {
        if(go->next!=NULL) go=go->next;
    }
    if (r2 == (*kolSTR))
    {
        go=(*End);
        if (*End)  (*End)->next=NULL;
    }
    for(w=0; w <= (r2-r1); w++)
    {
        if((go!=NULL)&&(go->next!=NULL))del=go->next;
        if((del!=NULL)&&(del->next!=NULL))
        {
            go->next = del->next;
            (del->next)->prev=go;
        }
        else
        {
            go->next=NULL;
        }

        if((del!=NULL))
        {
            free(del->s);
        }
        if(del!=NULL)
        {
            (*kolSTR)--;
            free(del);
        }
    }
    free (arguments1);
    free (arguments2);
    if(exit_eof==1)
        return OK_EXIT
    else
        return OK;
}
