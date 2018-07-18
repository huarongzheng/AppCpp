#include<stdio.h>
/**   
 * @ parami  n the input number to count for 1s
 * @ return  the number of ones in input n
 */    
unsigned int countSetBits(int n)
{
    unsigned int count = 0;
    while (n)
    {
        n &= (n-1) ;
        count++;
    }
    return count;
}

/* Program to test function countSetBits */
int main()
{
    int i = 9;
    printf("%d\n", countSetBits(i));
    return 0;
}
