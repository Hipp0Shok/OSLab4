#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define        R  0        /*  stdin                      */
#define        W  1     /*  stdout                    */
#define        TRUE  1
#define        FALSE 0
#define        PERIOD '.'
void main(void)        /*  Textcount.c  */
    {
        int pid;
        int p[2], q[2];
        FILE *fp;
        char c;
        int newline = TRUE;
        int total;

/* Установка программных каналов p и q */
        pipe(p);
        pipe(q);
/* p[R], q[R] - концы каналов для чтения  */
/* p[W], q[W] - концы каналов для записи  */
        switch(pid = fork())
        {
            case 0:  /*  ПОТОМОК  */
                            /*    читает из  p[R]    */
                            /*    пишет в    q[W]    */
                            /*    p[W] и  q[R]  - закрыты    */
                            /*    станд. ввод и p[R] - синонимы    */
                            /*    станд. вывод и q[W]   синонимы    */
        /*        Канал    P     */
                close(p[W]);
                close(R);
                dup(p[R]);
                close(p[R]);
                            /* Теперь станд. ввод и p[R] -  синонимы  */
        /*        Канал Q         */
                close(q[R]);
                close(W);
                dup(q[W]);
                close(q[W]);

    /* Теперь станд. вывод и  q[W] - синонимы  */
    /* Запуск внешней независимой программы Count */
                execl("./count", "count", NULL);
                printf("textcount: Ошибка при вызове");
                exit(1);
            case -1: /* Cбой при вызове fork()  */
                printf("Ошибка при вызове fork() \n");
                exit(1);
            default:   /* Это ПРЕДОК   */
                    /*  Конец канала P преобразуется для */
                    /*  записи в поток */
                close(p[R]);
                close(q[W]);
                fp = fdopen(p[W], "w");
/* Посылка текстового файла в процесс COUNT  */ 
            while((c=getchar()) != EOF )
            {
                switch(newline)
                    {
                        case TRUE:
                            if (c == '\n')  /* Пустая строка  */
                                putc(c, fp);
                            else if (c == '.')
                            {
                                do
                                {
                                    c = getchar();
                                }while(c != '\n' && c != EOF);
                            }
                            else
                            {
                                putc(c, fp);
                                newline = FALSE;
                            }
                            break;
                        default:
                            putc(c, fp);
                            if (c == '\n')
                            {
                                newline = TRUE;
                            }
                    }
            }
            fclose(fp);     /* Чтобы принимающий процесс мог воспринимать */
                     /* EOF  на конце канала для чтения            */
    /* Теперь подключаем ввод результата  */
    /* из канала Q                        */
        close(R);  dup(q[R]); close(q[R]);
        scanf("%d", &total);
        printf("Общее число знаков  %d\n", total);
        exit(0);
        }
    }
