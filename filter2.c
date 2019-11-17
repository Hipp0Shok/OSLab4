#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 81

void outputStr(char* str)
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
		putchar(*str);
	}
	putchar(*str);
}

int main(void)
{
	char buff[LENGTH];
	char *str;
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
		outputStr(buff);
	}
	return 0;
}