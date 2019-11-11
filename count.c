#include <stdio.h>
void main(void)  /*  COUNT.C  */
            /*  Процесс, выполняющий  COUNT,  должен    */
            /*  переназначить ввод и вывод так,    */
/*  чтобы ввод данных выполнялся из канала P,     */
/*  а вывод – в канал Q    */
            /*        */
{
    int count = 0;
    while (getchar() != EOF)
    count++; printf("%d\n", count);
}
