#include <bits/stdc++.h>
#include <assert.h>

#include <map>
#include <set>
#include <list>
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

using namespace std;

#define MAX_roll
/**
 * @param n number of times left
 */
float RollDice(int n)
{
    if (n==0)
    {
        return (1+2+3+4+5+6)/6.0;
    }
    else
    {
        float fResult = 0;
        float fExpect = RollDice(n-1);
        for (unsigned uVal=6; uVal>0; uVal--)
        {
            if ((float)uVal>fExpect)
            {
                fResult += uVal/6.0;
            }
            else
            {
                fResult += fExpect/6.0;
            }
        }
        return fResult;
    }
}

int main()
{
    ifstream cin("input");

    int nTimeLeft, t = 0;
    cin >> t;
    for (int i=0; i<t; ++i)
    {
        cin >> nTimeLeft;
        cout << RollDice(nTimeLeft) << "\n";
    }

    return 0;
}
