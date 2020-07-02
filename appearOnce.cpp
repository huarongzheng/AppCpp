/* given a string (1<=len<=10000) find the first character that only appear once, return it*/
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<map>
#include<iostream>

using namespace std;
/**
 * @param[in] str the given string
 * @return the first character that only appear once
 */
char FirstOnceChar(char *str)
{
    if(str == NULL)
        return '\0';

    int hashtable[256];
    memset(hashtable,0,sizeof(hashtable));
    char *pCur = str;
    while(*pCur != '\0')
    {
        if(*pCur>=0)
            hashtable[*(pCur++)]++;
        else
            hashtable[*(pCur++)+256]++;
    }

    while(*str != '\0')
    {
        int index;
        if(*str>=0)
            index = *str;
        else
            index = *str+256;

        if(hashtable[index] == 1)
            return *str;
        else
            str++;
    }
    return '\0';
}

/**
 * @param[in] str the given string
 * @return the first character that only appear once
 */
int IndexOfFirstOnceChar(char *str)
{
    if(str == NULL)
        return -1;

    int len = strlen(str);
    int hashtable[256];
    memset(hashtable,0,sizeof(hashtable));
    int i;
    for(i=0;i<len;i++)
    {
        if(str[i]>=0)
            hashtable[str[i]]++;
        else
            hashtable[str[i]+256]++;
    }

    for(i=0;i<len;i++)
    {
        int index;
        if(str[i]>=0)
            index = str[i];
        else
            index = str[i]+256;

        if(hashtable[index] == 1)
            return i;
    }
    return -1;
}

int main()
{
    char result = '\0';
    //char str[] = "hasahdjsa";
    //char str[] = "JUJCGGXXT";
    //char str[] = "AA137123451BACC5gDeF012fbclY39876";
    char *str=new char[4]{'O','M','O','\0'};

    long beginTime = clock();
    for (int i = 0; i < 1000; ++i)
    {
        result = FirstOnceChar(str);
    }
    long endTime = clock();

    printf("%c\n",result);
    //cout<<"beginTime:"<<beginTime<<"  endTime:"<<endTime<<endl;
    cout<<"Time: "<<double(endTime-beginTime)/CLOCKS_PER_SEC<<endl;
    return 0;
}
