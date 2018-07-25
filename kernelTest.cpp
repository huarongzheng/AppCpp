#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<vector>
#include<array>
#include<iostream>
#include<time.h>
#include<algorithm>

using namespace std;

#define offsetof(type, member) ((size_t) &((type*)0)->member) // & is applied to member
#define container_of(ptr, type, member) ({                      \
                      const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
                       (type *)( (char *)__mptr - offsetof(type,member) );})

struct TestStruct {
    int   num;
    char  ch;
    float fVal;
};
struct TestStruct1 {
    int   num;
    char  ch;
    char  ch1;
    char  ch2;
    float fVal;
};

int main()
{
    printf("offset is %u\n", offsetof(TestStruct, fVal));

    TestStruct testArray[10];
    int i=0;
    for (auto &ele : testArray) {
        ele.num = i;
        i++;
    }
    cout << sizeof(TestStruct1)<< endl;
    cout << (testArray)<< endl;
    printf("addr=0x%lx\n", (char *)testArray+1);

    TestStruct *test;
    TestStruct init_struct={12,'a',12.3};
    char *pCh = &init_struct.ch;
    test = container_of(pCh, TestStruct, ch);
    printf("TestStruct->num =%d\n", test->num);
    printf("TestStruct->ch =%c\n",  test->ch);
    printf("TestStruct->ch =%f\n",  test->fVal);
    return 0;
}
