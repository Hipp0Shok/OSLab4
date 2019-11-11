#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LEFT 10
#define RIGHT 10
#define LENGTH 81

int printBorder(int charCount, int amount)
{
	if(charCount > amount)
	{
		for(int i = 0; i < amount; amount++)
		{
			putc(' ');
		}
	}
	else
	{
		return -1;
	}
	return charCount - amount;
}

void main(void) 
{
	int charCount = LENGTH - LEFT - RIGHT - 1; //length-left-right-'\n'
	charCount = printBorder(charCount, LEFT);




}