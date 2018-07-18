#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<vector>
#include<iostream>
#include<time.h>
#include <algorithm>

using namespace std;

typedef void (*fVoid)();

class Base
{
public:
    virtual void f() { cout << "Base::f" << endl; }
    virtual void g() { cout << "Base::g" << endl; }
    virtual void h() { cout << "Base::h" << endl; }
    void i() { cout << "Base::i" << endl; }
};

class A
{
public:
    static void test()
    {
        printf("hello A\n");
    }

    A()
    {
        print = A::test;
    }

    fVoid print;
};

class B: public A
{
public:
    static void test()
    {
        printf("hello B\n");
    }

    B()
    {
        print = B::test;
    }
};

void foo()
{
}

int main()
{
    A a;
    a.print();

    B b;
    A *pA = &b;
    pA->print();
    cout << sizeof(pA->print) << endl;


    typedef void(*Fun)(void);
    Base c;
    Fun pFun = NULL;
    cout << sizeof(long) << endl;
    long lFuncAdr = *(long*)(&c);
    cout << "虚函数表地址：" << (long*)(&c) << endl;
    printf("%p\n", &Base::h); // <<hex << (&foo) always give 1, doesn't work
    cout << "虚函数表 — 第一个函数地址：" <<hex  << *((long*)lFuncAdr) << endl;
    // Invoke the first virtual function
    pFun = (Fun)*((long*)lFuncAdr + 0);
    printf("%p\n", pFun);
    pFun();
    pFun = (Fun)*((long*)lFuncAdr + 1);
    printf("%p\n", pFun);
    pFun();
    pFun = (Fun)*((long*)lFuncAdr + 2);
    printf("%p\n", pFun);
    pFun();

    return 0;
}

