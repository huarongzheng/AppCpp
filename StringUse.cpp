#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <exception>
using namespace std;


#include <assert.h>
#include <vector>

#define INIT_VAL (0)
#define TOTAL_NUM (2)
typedef unsigned long u32_t;
typedef long s32_t;
//typedef vector<vector<u32_t> *> vectorpt_t;

typedef vector<string>::iterator iter_t;

void SwapChar(string *a, string *b)
{
    char sHead;
    sHead = (*a)[0];
    (*a)[0] = (*b)[0];
    (*b)[0] = sHead;
}

void StringSplit(const string s, const string delim, vector<string> &splited)
{
    size_t begin = 0;
    size_t end, endCalc;
    string part;
    /*
    size_t end = s.find(delim, begin);

    while (end != string::npos)
    {
        if (begin != end)
        {
            part = s.substr(begin, end-begin);
            splited.push_back(part);
        }
        begin = end+1;
        end = s.find(delim, begin);
    }
    */

    do
    {
        end = s.find(delim, begin);

        if (end == string::npos)
        {
            endCalc = s.size();
        }
        else
        {
            endCalc = end;
        }

        if (begin != endCalc)
        {
            part = s.substr(begin, endCalc-begin);
            splited.push_back(part);
        }

        begin = end+delim.size();
    }
    while (end != string::npos && begin < s.size());
}

int main() {

    ifstream cin("input");

    vector<string> str;
    string temp;
#if 0
    while (cin>>temp)
    {
        for (unsigned int j = 0; j < temp.length(); j++)
        {
            assert(((unsigned int)temp[j])>=((unsigned int)'a'));
            assert(((unsigned int)temp[j])<=((unsigned int)'z'));
        }
        str.push_back(temp);
    }

    temp="";
    for (iter_t it = str.begin(); it != str.end(); ++it)
    {
        cout<<it->size()<<" ";
        temp += *it;
    }
    cout<<endl<<temp<<endl;

    SwapChar(&str[0],&str[1]);
    cout<<str[0]<<" "<<str[1]<<endl;
#endif
    string cmd;
    vector<string> splited1, splited2;

#if 0
    while (getline(cin,cmd))
    {
        StringSplit(cmd, " ", splited1);
    }

    for (unsigned i=0; i<splited.size(); i++)
    {
        cout << "  in[" << i << "]=" << splited[i];
    }

    cout << endl;
#endif

    getline(cin,cmd);
    StringSplit(cmd, " ", splited1);
    getline(cin,cmd);
    StringSplit(cmd, " ", splited2);

    sort(splited1.begin(), splited1.end());
    sort(splited2.begin(), splited2.end());

    for (unsigned i=0; i<splited2.size(); i++)
    {
        cout << "  in[" << i << "]=" << splited2[i];
    }
    cout << endl;

    vector<string> intersect(splited1.size()+splited2.size());
    vector<string>::iterator intersectEnd;
    intersectEnd = set_intersection(splited1.begin(), splited1.end(), splited2.begin(), splited2.end(), intersect.begin());

    for (unsigned i=0; i<intersectEnd-intersect.begin(); i++)
    {
        cout << "  intersect[" << i << "]=" << intersect[i];
    }
    cout << endl;

}
