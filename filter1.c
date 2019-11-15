#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LEFT 20
#define RIGHT 20
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
	int strLen = 0, strWords = 0, emptyChar = 0, i =0;
	strInfo(str, &strLen, &strWords);
	emptyChar = LENGTH - LEFT - RIGHT - 1 - strLen;
	printBorder(LEFT);
	spaces = div(emptyChar, strWords-1);
	printf("%d, %d\n", spaces.quot, spaces.rem);
	while(strWords != 1)
	{
		putchar(*str);
		if(*str == ' ')
		{
			for(i = 0; i < spaces.quot; i++)
			{
				putchar('b');
			}
		}
		str++;
		strWords -= 1;
	}
	for(i = 0; i < spaces.rem; i++)
	{
		putchar(' ');
	}
	while(*str != '\n')
	{
		putchar(*str);
		str++;
	}
	printBorder(RIGHT);
	putchar('\n');
}

int main(void) 
{
	char buff[LENGTH - LEFT - RIGHT];
	fgets(buff, LENGTH - LEFT - RIGHT, stdin);
	outputStr(buff);
	return 0;
}