#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define        R  0        /*  stdin                      */
#define        W  1     /*  stdout                    */
#define        TRUE  1
#define        FALSE 0
#define        PERIOD '.'
int main(void)        /*  Textcount.c  */
    {
        int pid;
        int p[2], q[2];
        FILE *fp;
        int c;
        int newline = TRUE, delete = FALSE;
        int total;

/* Установка программных каналов p и q */
        pipe(p);
        pipe(q);
/* p[R], q[R] - концы каналов для чтения  */
/* p[W], q[W] - концы каналов для записи  */
        switch(pid = fork())
        {
            case -1:
                perror("Ошибка при вызове fork.");
                exit(1);
                break;
            case 0: /*Потомок*/
                dup2(p[R], 0);
                close(p[R]);
                close(p[W]);
                dup2(q[W], 1);
                close(q[W]);
                close(q[R]);
                execl("./count", "count", NULL);
                perror("Ошибка при вызове функции");
                exit(2);
                break;
            default: /*Предок*/
                close(p[R]);
                fp = fdopen(p[W], "w");

                while(1)
                {
                    c = getchar();
                    if( c == EOF)
                    {
                        if(feof(stdin))
                        {
                            break;
                        }
                        else
                        {
                            perror("Ошибка при считывании символа.\n");
                            exit(2);
                        }
                    }
                    if(newline)
                    {
                        if(c == '.')
                        {
                            delete = TRUE;
                        }
                        newline = FALSE;
                    }
                    if(c == '\n')
                    {
                        newline = TRUE;
                        delete = FALSE;
                    }
                    if(delete == FALSE)
                    {
                        putc(c, fp);
                    }
                }
                fclose(fp);
                dup2(q[R], 0);
                close(q[R]);
                scanf("%d", &total);
                printf("%d\n", total);
                exit(0);
        }
    }
