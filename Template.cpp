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

/*
#include <exception>
#include <stdexcept>
*/

using namespace std;

template <class T>
class Max
{
public:
    Max()
    {
    }

    ~Max()
    {
    }

    T GetMax(T a, T b)
    {
        return ((a>b) ? (a) : (b));
    }
};

int main()
{
    Max<char> myMax;

    cout << "max is " << myMax.GetMax('A', 'B') << endl;
    return 0;
}

