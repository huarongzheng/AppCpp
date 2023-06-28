/* given a string (1<=len<=10000) find the first character that only appear once, return it*/
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<map>
#include<iostream>

using namespace std;
/**
 * @param[in] str the given string
 * @param[in] pos of the first character that only appear once
 * @return the first character that only appear once
 */
char FirstOnceChar(char *str, int &pos)
{
    if(str == NULL)
        return '\0';

    int hashtable[256];
    memset(hashtable,0,sizeof(hashtable));
    char *pCur = str;
    while(*pCur != '\0')
    {
        if (*pCur>=0)
            hashtable[*(pCur++)]++;
        else
            hashtable[*(pCur++)+256]++;
    }

    pCur = str;
    while (*pCur != '\0')
    {
        int index;
        if (*pCur >= 0)
            index = *pCur;
        else
            index = *pCur + 256;

        if (hashtable[index] == 1) {
            pos = pCur - str;
            return *pCur;
        }
        else
            pCur++;
    }
    return '\0';
}

int main()
{
    char result = '\0';
    int  index{};
    //char str[] = "hasahdjsa";
    //char str[] = "JUJCGGXXT";
    char str[] = "AA137123451BACC5gDeF012fbclY39876";
    //char *str=new char[4]{'O','M','O','\0'};

    long beginTime = clock();
    for (int i = 0; i < 1000000; ++i)
    {
        result = FirstOnceChar(str, index);
    }
    long endTime = clock();

    printf("%c appears once on pos=%d\n", result, index);
    //cout<<"beginTime:"<<beginTime<<"  endTime:"<<endTime<<endl;
    cout<<"Time: "<<double(endTime-beginTime)/CLOCKS_PER_SEC<<endl;
    return 0;
}
