#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LEFT 20
#define RIGHT 10
#define LENGTH 81
#define TRUE 1
#define FALSE 0

void printBorder(int amount)
{
	for(int i = 0; i < amount; i++)
	{
		putchar(' ');
	}
}

int charCount(char* str)
{
	int amount = 0;
	while(*str != '\n')
	{
		amount++;
		str++;
	}
	return amount;
}

int wordCount(char* str, int len)
{
	int flag = FALSE;
	int amount = 0;
	while(*str != '\n')
	{
		if(*str != ' ')
		{
			if(!flag)
			{
				amount++;
				flag = TRUE;
			}
		}
		else
		{
			flag = FALSE;
		}
		str++;
	}
	return amount;
}

void strInfo(char* str, int* strLen, int* strWords)
{
	*strLen = charCount(str);
	*strWords = wordCount(str, *strLen);
}

void outputStr(char* str)
{
	div_t spaces;
	int strLen = 0, strWords = 0, emptyChar = 0, i = 0, j = 0;
	int prevSymbol = TRUE;
	strInfo(str, &strLen, &strWords);
	emptyChar = LENGTH - LEFT - RIGHT - 1 - strLen;
	printBorder(LEFT);
	if(strWords == 1)
	{
		for(j = 0; j < strLen; j++)
		{
			putchar(*str);
			str++;
		}
		for(j = 0; j < emptyChar; j++)
		{
			putchar(' ');
		}
	}
	else
	{
		spaces = div(emptyChar, strWords-1);
		for(j = 0; j < strLen; j++)
		{
			if(*str == ' ')
			{
				if(prevSymbol == TRUE)
				{
					for(i = 0; i < spaces.quot; i++)
					{
						putchar(' ');
					}
					if(spaces.rem != 0)
					{
						putchar(' ');
						spaces.rem -= 1;
					}
					prevSymbol = FALSE;	
				}
			}
			else
			{
				if(prevSymbol == FALSE)
				{
					prevSymbol = TRUE;
				}
			}
			putchar(*str);
			str++;
		}
	}
	printBorder(RIGHT);
	putchar('\n');
}

int main(void) 
{
	char buff[LENGTH - LEFT - RIGHT];
	char *str;
	while(1)
	{
		str = fgets(buff, LENGTH - LEFT - RIGHT, stdin);
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