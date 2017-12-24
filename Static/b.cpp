#include <cstdio>
#include <iostream>
extern int foo();
int a = 21;
using namespace std;
int main()
{
    int &c = a;
    int *d = new int[10];
    cout << c << " " << foo() << endl;
    delete d;
    return 0;
}
