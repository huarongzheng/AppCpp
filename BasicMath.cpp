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
#include <assert.h>
using namespace std;

int Add(int a, int b)
{
    cout << "Add ";
    int sum = a ^ b;
    int carry = a & b;
    while (carry != 0) {
        a = sum;
        b = carry << 1;
        sum = a ^ b;
        carry = a & b;
    }

    return sum;
}

int Neg(int n)
{
    cout << "Neg ";
    return Add(~n, 1);
}

int Sub(int a, int b)
{
    cout << "Sub ";
    return Add(a, Neg(b));
}

int Mul(int a, int b)
{
    cout << "Mul ";
    int nResult = 0;
    bool bNeg = false;
    int nBitCnt = 0;
    if (b < 0)
    {
        b = Neg(b);
        bNeg = true;
    }

    //int mask=0;
    while ((1<<nBitCnt)>0)
    {
        //nResult += (b & (1 << nBitCnt)) ? (a << nBitCnt) : 0 ;
        nResult = Add(nResult, (b & (1 << nBitCnt)) ? (a << nBitCnt) : 0) ;
        //cout << nResult << " " << (1<<nBitCnt) << endl;
        nBitCnt++;
    }

    if (bNeg)
    {
        nResult = Neg(nResult);
    }

    return nResult;
}


int main()
{
    int op1, op2;
    cin >> op1 >> op2;
    cout << Mul(op1, op2) << endl;
}

