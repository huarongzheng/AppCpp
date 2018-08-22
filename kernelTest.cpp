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
#include<typeinfo>

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

struct BitField{
    int a:5; // char is at least 1 byte, int at lesat 4
    int b:3;
    //int c:3; //no straddling byte
};

struct Flex {
    union {   // union U is defining an union not declaring one thus no size. here the declaration is of size 4
        int   num;
        char  ch;
    };
    int buf[0];
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
    cout << (testArray)<< endl;
    printf("addr=0x%lx\n", (long unsigned)(char *)testArray+1);

    TestStruct *pTest;
    TestStruct init_struct={12,'a',12.3};
    char *pCh = &init_struct.ch;
    pTest = container_of(pCh, TestStruct, ch);
    printf("TestStruct->num =%d\n", pTest->num);
    printf("TestStruct->ch =%c\n",  pTest->ch);
    printf("TestStruct->ch =%f\n",  pTest->fVal);


    TestStruct1 *pTest1=new TestStruct1();
    cout << sizeof(TestStruct1) << endl;
    pTest1->num = &i;
    cout << *pTest1->num << endl; // that is *(pTest1->num) -> triumph * or &


    Flex flex;
    cout << "size of Flex " << sizeof(Flex) << endl;
    cout << "address flex=" << (&flex)<< " flex+1=" << (&flex)+1 << endl;
    cout << "type of flex " << typeid((&flex)+1).name() << endl;
    flex.num=4321;
    typeof(&flex+1) __tmp = &flex;
    cout << "flex num " << __tmp->num << endl;

    //'0' = 0011 0000     'l'  = 0110 1100
    char str[100] = "0134324324afsadfsdlfjlsdjfl";
    BitField bitField;
    cout << sizeof(BitField) << endl;
    memcpy(&bitField, str, sizeof(BitField));
    cout << bitField.a << endl;
    cout << bitField.b << endl;

    int x=1;
    if (*(char *) &x == 1) {
        cout << "little endian" << endl;
    } else {
        cout << "big endian" << endl;
    }

    return 0;
}
