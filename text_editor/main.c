#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h> 
#include <wchar.h>
#include <locale.h>

#include "alllib.h"
#include "call_command.h"
#include "syscomand.h"
#include "insert_afters.h"

/*
 *         beginlist
 *       Собственно функция, заполняет изначальное хранение строк из начального файла.
 *      На вход принимает
 *  FILE* file    указатель на файл
 *  struct stroki ** Begin     указатель на указатель на начало списка строк. Причем первая строка хранится в Begin->next
 *  struct stroki ** End       указатель на указатель на последнюю строчку
 *  int * kolSTR    хранит указатель на кол-во строк.
 */

int beginlist(FILE* file, struct stroki** End,int* kolSTR)
{
    wchar_t c=L'\0';
    wchar_t now=L'\0';
    wchar_t next=L'\0';
    wchar_t control_=L'\0';
    wchar_t *f;
    wchar_t* line =(wchar_t*)malloc(100*sizeof(wchar_t));
    int y = 100;
    int k=0;
    int i=0;

    while(1)
    {
        wint_t wc;
        wc = fgetwc(file);
        control_ = now;
        now = next;
        next = wc;

        if ((control_ == L'\\') && (now == L'\\') && ((next == L'n') || (next == L'r') || (next == L't')))
        {


        }
        else
        {
            while (((control_ != L'\\')||(control_==L'\0')) && (now == L'\\') && ((next == L'n') || (next == L'r') || (next == L't')))
            {


                if (next == L'r')
                {
                    control_ = L'\0';
                    now = L'\r';
                    wc = fgetwc(file);
                    next = wc;
                }
                if (next == L't')
                {
                    control_ = L'\0';
                    now = '\t';
                    wc = fgetwc(file);
                    next = wc;
                }
                if (next == L'n')
                {
                    now = L'\n';
                    next = L'\0';
                    control_ = L'\0';
                }
            }
            c = now;
            if ((c != L'\n'))
            {
                if (wc == WEOF)
                {
                    free(line);
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
                        struct stroki *NewElement = calloc(1, sizeof(struct stroki));
                        (*kolSTR)++;
                        NewElement->s = line;
                        NewElement->prev = (*End);
                        NewElement->sizeS = k;
                        (*End)->next = NewElement;
                        *End = NewElement;
                        if(*End) (*End)->next = L'\0';
                        c=L'\0';
                        now=L'\0';
                        next=L'\0';
                        control_=L'\0';
                        line = (wchar_t *) malloc(100 * sizeof(wchar_t));
                        y = 100;
                        k = 0;
                        i = 0;
                    }

                }
                else
                {
                    f = realloc(line, y * 2 * sizeof(wchar_t));
                    if (f==NULL)
                    {
                        free(line);/*так и только так. Нам не хватает памяти выделить под объект для хранеия строки*/
                        return LOCK;
                    }
                    else
                    {
                        line=f;
                    }
                    y = y * 2;
                }
            }

            else
            {



                struct stroki *NewElement = calloc(1, sizeof(struct stroki));
                (*kolSTR)++;
                NewElement->s = line;
                NewElement->prev = (*End);
                NewElement->sizeS = k;
                (*End)->next = NewElement;
                *End = NewElement;
                if (*End)  (*End)->next=L'\0';
                c=L'\0';
                now=L'\0';
                next=L'\0';
                control_=L'\0';
                line = (wchar_t *) malloc(100 * sizeof(wchar_t));
                y = 100;
                k = 0;
                i = 0;


                if (wc == WEOF)
                {
                    free(line);
                    break;
                }
            }
        }

    }
    return OK;
}


/*
 *            main.
 *      Изначальная функция.
 *  На вход принимает один необязательный аргумент. Это путь к файлу, который будет у нас по умолчанию.
 *  Собственно вызывает beginlist с данным названием. Чтобы хранить информацию из файла в виде списка.
 * Возвращает значение, с каким завершилась работа программы.
 */

int main(int argc,char* argv[])
{
    int r=0;
    char * setname =(char*)malloc(100*sizeof(char));
    int setnamenow=0;
    int setnamemax=100;
    struct stroki Now;     /*Нахуй*/
    int kolHelp=0;
    struct stroki* BeginHelp;
    struct stroki* EndHelp;
    struct stroki NowHelp;
    struct stroki* del;
    int kolSTR=0;
    int numbers=0;
    int wrap=1;
    int tab=8;
    int z;
    struct stroki* Begin;
    struct stroki* End;
    wchar_t string1[508];
    wchar_t string2[508];
    wchar_t string3[508];
    wchar_t string4[508];
    wchar_t string5[508];
    wchar_t string6[508];
    wchar_t string7[508];
    wchar_t string8[508];
    wchar_t string9[690];
    wchar_t string10[600];

    setlocale(LC_ALL,"");
    Begin=&Now;
    End=&Now;
    Begin->next=End;
    End->prev=Begin;
    End->next=NULL;
    NowHelp.s=NULL;
    NowHelp.next=NULL;
    NowHelp.prev=NULL;
    NowHelp.sizeS=0;
    BeginHelp=&NowHelp;
    EndHelp=&NowHelp;
    BeginHelp->next=EndHelp;
    EndHelp->prev=BeginHelp;
    EndHelp->next=NULL;

    kolHelp=-1;
    wcscpy(string1,L"Вывод на экран:\\n\\n 1)set tabwidth n\\n\\tНа вход принимает число n.Заменяет все отступы(таб) на n пробелов при выводе на экран. На вход принимает число.\\n\\tПример:\\n\\tset tabwidth 3\\n\\n 2)set numbers s\\n\\tПринимает на вход s=yes или s=no. В зависимости от это включает нумерацию строк при выводе на экран или нет.\\n\\tПример:\\n\\tset numbers yes\\n\\n 3)set wrap s\\n\\tПринимает на вход s=yes или s=no. В зависимости от это включает обрезание строк при выводе на экран или нет.\\n");
    string1[473]=L'"';
    string1[474]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string1,-1);
    kolHelp=-1;
    del=EndHelp;
    EndHelp=EndHelp->prev;
    EndHelp->next=NULL;
    free(del->s);
    free(del);
    wcscpy(string2,L" \\tПример:\\n\\tset wrap no\\n\\n 4)print pages\\n\\tСобственно выводит на экран весь текст с учетом влияния функций set tabwidth, set numbers, set wrap.\\n\\n 5)print range x,y\\n\\tНа вход принимает два числа. Второе не обязательно. И выводит текст в диапазоне [x,y] строк, где x,y номера строк. Eсли y не указано, то выводит до конца с позиции x.\\n\\tПример:\\n\\tprint range 1 3\\n\\n\\nГруппа команд вставки строк:\\n\\n 1)insert after n s\\n");
    string2[425]=L'"';
    string2[426]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string2,-1);
    kolHelp=-1;
    wcscpy(string3,L" \\tПринимает на вход необязательное число n, то есть если n не указано, то вставляется после последней строки. А так же принимает строку, заковыченную одиночными ковычками. Все, что внутри ковычек, вставляется после n строки.\\n\\tПример\\n\\ts=egfew.\\n\\tТак же может принимать текст заковычченный тремя ковычками с каждой стороны. Тогда там возможна группа строк, то есть вставка срауз нескольких строк, через введение '\\n' после каждой строчки.\\n\\tПример: \\n\\tinsert after \\n");
    string3[470]=L'"';
    string3[471]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string3,-1);
    kolHelp=-1;
    wcscpy(string4,L"/*Здесь будет конец моей\\n *программы на Си\\n *Спасибо, что дочитали код\\n */\\n\\n\\n\\nГруппа команд редактирования строк:\\n\\n 1)edit string n m\\n\\tПозволяет заменить символ в n-ой строке начиная с m-ой позиции; после указания позиций следует заменяемый символ. Если необходимо вставить специальный символ, то можно использовать '\\'.\\n\\tПример:\\nedit string 2 60000 ё\\n\\tзаменит символ во второй строке в позиции 60000.\\n\\n 2)insert symbol n m \\n");
    string4[442]=L'"';
    string4[443]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string4,-1);
    kolHelp=-1;
    wcscpy(string5,L" \\t Команда заменяет симвод в n строке m позции на введенный. Если m выходит за диапазон, то:вправо-вставляем вконец, влево-вставляем вначало.\\n\\tПример:\\n\\tinsert symbol 2 4 'f'\\n\\n 3)replace substring\\n\\tКоманда ищет и заменяет подстроки в диапазоне строк. После имени команды идёт диапазон строк. Если диапазон не указан, то поиск и замена происходит во всём тексте. Затем идут две строки в двойных ковычках, возможно каждая на новой строке.\\n");
    string5[446]=L'"';
    string5[447]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string5,-1);
    del=EndHelp;
    EndHelp=EndHelp->prev;
    EndHelp->next=NULL;
    free(del->s);
    free(del);
    kolHelp=-1;
    wcscpy(string6,L"Первая из них образец, которая будет найдена в тексте, следующая строка, на которую производится замена.\\n\\tСимвол '^' (вместо строки абразца) - означает, что строка приписывается в начало каждой строки из диапазона.\\n");
    string6[218]=L'"';
    string6[219]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string6,-1);
    del=EndHelp;
    EndHelp=EndHelp->prev;
    EndHelp->next=NULL;
    free(del->s);
    free(del);
    kolHelp=-1;
    wcscpy(string7,L"Символ '$' - означает, что приписывается в конец каждой строки из диапазона.\\n\\n 4)delete range n m\\n\\t удаляет строки из диапазона [n,m]\\n\\n 5)delete breces n m\\n\\t Удаляет группы символов, расположенные между фигурными скобками '{' и '}'. А так же удаляет скобки. А так же может быть указан диапазон [n,m] в котором надо удалять, если не указан, то во всем тексте. Если нет второй закрывающей скобки, то до конца диапазона(текста) происходит удаление.\\n\\n\\nГруппа технических команд:\\n\\n");
    string7[489]=L'"';
    string7[490]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string7,-1);
    del=EndHelp;
    EndHelp=EndHelp->prev;
    EndHelp->next=NULL;
    free(del->s);
    free(del);
    kolHelp=-1;
    wcscpy(string8,L"1)exit\\n\\t Осуществляет вызов из текстового редактора, если текст не сохранен, ты выдается предупреждение и выход не осуществляется, если все равно необходимо выйти, то вводится команда exit force.\\n\\n 2)read\\n\\tОткрывает файл, и в случае удачи замещает им все строчки текста. Имя файла не запоминается для последующего сохранения текста в файл. Если текстом уже было ассоциировано какое-то имя, оно не будет затронуто командой. Имя файла в команде указывается в двойных ковычках.\\n\\n");
    string8[484]=L'"';
    string8[485]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string8,-1);
    del=EndHelp;
    EndHelp=EndHelp->prev;
    EndHelp->next=NULL;
    free(del->s);
    free(del);
    kolHelp=-1;
    wcscpy(string9,L"3)write\\n\\tСохраняет теккст в файл, если имя файла не указано, то запись происходит в запомненное имя файла. Если имя не ассоциировано, то диагностирует ошибку. Если имя файла было указано,а с текстом было ассоциирован файл, то ассоциация не изменяется. Если ассоциация была пустой, то берётся ассоциация из данной команды.\\n\\n 4)set name\\n\\tЗадает ассоциацию с именем файла. Задается строкой в двойных кавычках. Если строка пустая, то ассоциация удаляется.\\n\\n");
    string9[461]=L'"';
    string9[462]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string9,-1);
    del=EndHelp;
    EndHelp=EndHelp->prev;
    EndHelp->next=NULL;
    free(del->s);
    free(del);
    kolHelp=-1;
    wcscpy(string10,L"5)help\\n\\tПечатает помощь по текстовому редактору для пользователей.");
    string10[68]=L'"';
    string10[69]=L'\n';
    insert_after(&BeginHelp,&EndHelp,&kolHelp,1,string10,-1);
    kolHelp = 86;
    kolSTR=0;

    /*
     * нужное условие для того, чтобы каждый раз в командной строке не вводить каждый раз первый файл.
    if (1)
    {

        FILE *file;
        file=fopen("/home/tiger/CLionProjects/texteditor/sef.txt","r");
        beginlist(file,&Begin,&End,&kolSTR);
        fclose(file);
    }
     */
    if (argc>1)
    {
        FILE *file;
        file=fopen(argv[1],"r");
        if (file==NULL)
        {
            r=ERROR_OPEN_FILE;
            r=name_mistake(r,&Begin,&BeginHelp);
            return r;
        }
       z= beginlist(file,&End,&kolSTR);
        if (z)
        {
            z= r=name_mistake(z,&Begin,&BeginHelp);
            return z;
        }
        fclose(file);
    }

    r=command(&Begin,&End,&kolSTR,&numbers,&wrap,&tab,&BeginHelp,&kolHelp,setname,&setnamenow,&setnamemax);



    r=name_mistake(r,&Begin,&BeginHelp);
    free(setname);
    return r;

}


