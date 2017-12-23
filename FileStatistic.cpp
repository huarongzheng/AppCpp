#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <stdarg.h>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

#define IN 1
#define OUT 0
int main()
{
    FILE *fp;
    int length;
    fp = fopen("input", "r");//打开要计数的文件
    if (fp == NULL)
    {
        printf("can not open file");
        exit(0);
    }
    fseek(fp, 00, SEEK_END);
    length = ftell(fp);
    printf("%d\n", length);//确定所要查找的文件中总字符数长度，并在屏幕中显示出来
    rewind(fp);
    char str[100000], c;
    fread(str, sizeof(char), length, fp);//从文件中读取所有的字符到str序列
    int i, num1 = 0, num2 = 0, num3, num4=0, word = OUT;
    for (i = 0; (c = str[i]) != '\0'; i++)
    {
        if (c == ' ')//判断字符中单词数
        {
            num2++;
            word = OUT;
        }
        else
        {
            if (word == OUT)
            {
                word = IN;
                num1++;
            }
        }
        if ((c = str[i]) == '\n')
        {
            num4++;
            word = OUT;
        }
    }
    num3 = length - num2-num4;//字符数
    //num4++;//行数
    fclose(fp);
    printf("空格数为%d\n", num2);
    printf("单词数为%d\n行数为%d\n字符数为%d\n", num1, num4, num3);

    return 0;
}
