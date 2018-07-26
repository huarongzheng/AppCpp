#include<stdio.h>
#include<memory.h>
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
    int  *num;
    char  ch;
    float fVal;
    char  ch1;
};

struct TestStruct2 {
    char a:3;
    char b:3;
    char c:3;
    char d:3;
    char e:3;
};
struct A{
    int a:5;
    int b:3;
};

int main()
{
    printf("offset is %lu\n", offsetof(TestStruct, fVal));

    TestStruct testArray[10];
    int i=0;
    for (auto &ele : testArray) {
        ele.num = i;
        i++;
    }
    cout << sizeof(TestStruct1)<< endl;
    cout << sizeof(TestStruct2)<< endl;
    cout << (testArray)<< endl;
    printf("addr=0x%lx\n", (long unsigned)(char *)testArray+1);

    TestStruct *pTest;
    TestStruct init_struct={12,'a',12.3};
    char *pCh = &init_struct.ch;
    pTest = container_of(pCh, TestStruct, ch);
    printf("TestStruct->num =%d\n", pTest->num);
    printf("TestStruct->ch =%c\n",  pTest->ch);
    printf("TestStruct->ch =%f\n",  pTest->fVal);

    TestStruct1 *pTest1;
    pTest1->num = &i;
    cout << *pTest1->num << endl; // that is *(pTest1->num) -> triumph * or &

    int a[0];
    a[0] = 1;
    cout << a[0] << " " << sizeof(a[0]) << " " << sizeof(a) << endl;

    //'0' = 0011 0000     'l'  = 0110 1100
    char str[100] = "0134324324afsadfsdlfjlsdjfl";
    struct A d;
    memcpy(&d, str, sizeof(A));
    cout << d.a << endl;
    cout << d.b << endl;

    return 0;
}
