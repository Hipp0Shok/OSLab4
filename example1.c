#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
void main(void)        /*  LSWS.C                    */
                /*  Создание программного канала    */
                /*  для команд ls и wc                 */
    {
        int pid, pid2;
        int fd[2];
        int status, dead;
    switch(pid = fork())
            {
                case -1: /* Cбой при вызове fork()  */
                    printf("Ошибка при вызове fork() #1 \n");
                    exit(1);
                    break;
                case 0:  /*  ПОТОМОК #1 */
                    pipe(fd);
                    
                    switch(pid2 = fork())
                        {
                            case -1: /* Cбой при вызове fork()  */
                        printf("Ошибка при вызове fork() #2 \n"); 
                    exit(2);
                    break;
                    case 0:        /*  ПОТОМОК  #2 */
                            close(0); dup(fd[0]); close(fd[0]); close(fd[1]);
                            execl("/usr/bin/wc", "wc", NULL);
                            puts("Ошибка при вызове WC \n");
                            exit(-1);
                            break;
                    default: /*                     */
                            close(1); dup(fd[1]);
                            close(fd[1]); close(fd[0]);
                            execl("/bin/ls", "ls", NULL);
                            break;
                        }
                    puts("Ошибка при вызове LS\n");
                    exit(-1);
                default: /*  ПРЕДОК ГЛАВНЫЙ  */
                dead = wait(&status);
                exit(0);
                break;
    }
}
