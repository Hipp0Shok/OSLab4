#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
	int pid;
	int fd[2];
	pipe(fd);
	switch(pid = fork())
	{
		case -1:
			perror("Ошибка при создании потомка\n");
			exit(-1);
			break;
		case 0: //Потомок
			dup2(fd[1], 1); //пайп на запись stdout = fd[1]
			close(fd[0]);
			close(fd[1]);
			execl("./filter1", "filter1", NULL);
			perror("Ошибка при вызове первого фильтра\n");
			exit(-1);
			break;
		default: //Предок
			dup2(fd[0], 0); //пайп на чтение stdin = fd[0]
			close(fd[0]);
			close(fd[1]);
			execl("./filter2", "filter2", NULL);
			perror("Ошбка при вызове второго фильтра\n");
			exit(-1);
	}
	return 0;
}