#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LENGTH 81

void outputStr(char* str, FILE *flow)
{
	//Вывод строки
	int strLen = strlen(str);
	for(int i = 0; i < strLen - 1; i++, str++)
	{
		if(*(str) == ' ' && *(str + 1) == ' ')
		{
			*str = ':';
			*(str + 1) = '3';
		}
		fputc(*str, flow);
	}
	fputc(*str, flow);
}

int main(void)
{
	int p[2], q[2], pid; // p - передача во вторую q - приём из второй
	FILE* reverseFlow;
	char buff[LENGTH];
	char *str;
	pipe(p);
	pipe(q);
	switch(pid = fork())
	{
		case -1: //Ошибка
			perror("Ошибка при создании потомка\n");
			exit(-1);
			break;
		case 0: //Потомок
			dup2(p[0], 0); //stdin = p[0]
			close(p[0]);
			close(p[1]);
			dup2(q[1], 1); //stdout = q[1]
			close(q[0]);
			close(q[1]);
			execl("./filter1", "filter1", NULL);
			perror("Ошибка при вызове filter1\n");
			return -1;
			break;
		default: //Предок
			reverseFlow = fdopen(p[1], "w");
			close(p[0]);
			while(1)
			{
				str = fgets(buff, LENGTH, stdin);
				if( str == NULL)
				{
					if( feof(stdin))
					{
						break;
					}
					else
					{
						printf("Произошла ошибка при считывании\n");
						break;
					}
				}
				outputStr(buff, reverseFlow);
			}
			close(p[1]);
			fclose(reverseFlow);
			dup2(q[0], 0); //stdion = q[0]
			close(q[0]);
			close(q[1]);
			while(1)
			{
				scanf("%s\n", str);
				if( str == NULL)
				{
					if( feof == NULL)
					{
						break;
					}
					else
					{
						printf("Произошла ошибка при считывании\n");
						break;
					}
				}
				printf("%s\n", str);
			}
			return 0;
	}
}