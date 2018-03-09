#include <bits/stdc++.h>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <deque>
#include <vector>
#include <map>
#include <exception>
#include <stdexcept>
using namespace std;



#define LINE_LEN (200)
#define INVALID_NODE (-1)

typedef unsigned long u32_t;
typedef list<int>::iterator iter_t;


bool Cmp(int a, int b)
{
    return a > b;
}

class Matched
{
public:
    boxsz;
    melonsz;
}

int main(int argc, char *argv[]) {
    ifstream cin("input");
    int n; // number of workshops
    cin >> m >> n;
    // create arrays of unknown size n
    int *box = new int[n];
    int *boxAvail = new int[n];
    int *melon = new int[n];
    int *melonAvail = new int[n];

    for (int i=0; i < m; i++){
        cin >> box[i];
        boxAvail[i] = true;
    }
    for (int i=0; i < n; i++){
        cin >> melon[i];
        melonAvail[i] = true;
    }

    sort(box, box+m, Cmp);
    sort(melon, melon+n, Cmp);

    list<int> boxl(box);
    list<int> melonl(melon);
    list<Matched> matchedl;
    boxl.push_back(0); // for end compare

    iter_t boxit = boxl.begin();
    iter_t melonit = melonl.begin();
    while (melonl.end()<=boxl.front())
    {
        if ((*melonit)>(*boxit))
        {
            ++melonit;
        }
        else if ((*melonit) <= (*boxit) && (*melonit) > (*(boxit+1)))
        {
            Matched tmp;
            tmp.melonsz = *melonit;
            tmp.boxsz = *boxit;
            matchedl.push(tmp);
            melonit = melonl.erase(melonit);
            boxit = melonl.erase(boxit);
        }
        else if ((*melonit) <= (*boxit) && (*melonit) <= (*(boxit+1)))
        {
            ++melonit;
            ++boxit;
        }

        if (boxit==boxl.end())
        {
            boxit==boxl.begin();
        }

        if (melonit==melonl.end())
        {
            melonit==melonl.begin();
        }
    }

    //cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}

