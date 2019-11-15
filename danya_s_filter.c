#include <stdio.h>
#include <ctype.h>
int main(void) {
int c;
int b;
b=1;
while ((c = getchar()) != EOF)
{	if (c!='\n')
    {
		if (c != ' ' && b==1)
		{
			putchar(c);
			b = -1;
		}
		else if(b==-1)
		{
			putchar(c);
		}
	}
	else
		b=1;
}
return 0;
}