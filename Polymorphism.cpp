#include <stdio.h>
#include <iostream>
using namespace std;

class Parent
{
public:
    virtual ~Parent() {
        printf("~Parent()\n");
    }
    void F()
    {
        printf("Parent.F()\n");
    }
    virtual void G()
    {
        printf("Parent.G()\n");
    }

    //overload
    int Add(int x, int y)
    {
        return x + y;
    }
    float Add(float x, float y)
    {
        return x + y;
    }
};

class ChildOne: public Parent
{
public:
    ~ChildOne() {
        printf("~ChildOne()\n");
    }
    //重写(overwrite)父类函数
    void F()
    {
        printf("ChildOne.F()\n");
    }
    //覆写(override)父类虚函数,主要实现多态
    void G()
    {
        printf("ChildOne.G()\n");
    }
};


int main()
{
    Parent *p1 = new ChildOne();
    Parent *p2 = new Parent();
    ChildOne *p3 = new ChildOne();

    p1->F(); //调用Parent.F()
    p1->G(); //实现多态

    p2->F();
    p2->G();

    p3->F();
    p3->G();


    ChildOne *p4;
    //p4 = new Parent(); //compilation error: invalid conversion from ‘Parent*’ to ‘ChildOne*’ [-fpermissive]
    p4 = dynamic_cast<ChildOne *>(p1);
    cout << "cast C->P->C success result =" << p4 << endl;

    p4->F();
    p4->G();

    p4 = dynamic_cast<ChildOne *>(p2);
    cout << "cast P->C fail result =" << p4 << endl;
    Parent *p5 = dynamic_cast<Parent *>(p3);
    cout << "cast C->P success result =" << p5 << endl;

    p5->F();
    p5->G();


    //重载(overload)
    printf("%d\n",p2->Add(1, 2));
    printf("%f\n",p2->Add(3.4f, 4.5f));
    delete p1;
    delete p2;
    delete p3;
    return 0;
};
