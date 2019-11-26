#include <stdio.h>
#include <stdlib.h>
int main(void)  /*  COUNT.C  */
            /*  Процесс, выполняющий  COUNT,  должен    */
            /*  переназначить ввод и вывод так,    */
/*  чтобы ввод данных выполнялся из канала P,     */
/*  а вывод – в канал Q    */
            /*        */
/*Код не рабоатет верно с кириллицей. Используйте пока латиницу */
{
    int count = 0;
    int c;
    while (1)
    {
    	c = getchar();
    	{
    		if(c == EOF)
    		{
    			if(feof(stdin))
    			{
    				break;
    			}
    			else
    			{
    				perror("Error while trying to get char");
    				exit(1);
    			}
    		}
    	}
    	count++;	
    }
	printf("%d\n", count);
}
