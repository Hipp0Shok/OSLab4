#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LENGTH 81

void outputStr(char* str, FILE *stream)
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
		fputc(*str, stream);
	}
	fputc(*str, stream);
}

int main(void)
{
	int p[2], q[2], pid, temp; // p - передача во вторую q - приём из второй
	FILE* stream;
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
		case 0: //Потомок пишет в q[1], читает p[0]
			close(p[1]);
			close(q[0]);
			dup2(q[1], 1);
			close(q[1]);
			dup2(p[0], 0);
			close(p[0]);
			execl("./filter1", "filter1", NULL);
			perror("Ошибка при вызове первого фильтра\n");
			exit(-1);
			break;
		default: //Предок пишет в p[1], параллельно читает q[0]
			close(p[0]);
			close(q[1]);
			stream = fdopen(p[1], "w");
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
						perror("Произошла ошибка при считывании из stdin\n");
						exit(-1);
						break;
					}
				}
				outputStr(buff, stream);
			}
			fclose(stream);
			stream = fdopen(q[0], "r");
			while(1)
			{
				str = fgets(buff, LENGTH, stream);
				if( str == NULL)
				{
					if( feof(stream) )
					{
						break;
					}
					else
					{
						perror("Произошла ошибка при считывании из неименованного канала\n");
					}
				}
				printf("%s", buff);
			}
			fclose(stream);
			exit(0);
	}
	return 0;
}