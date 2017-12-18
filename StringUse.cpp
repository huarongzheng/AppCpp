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

int main() {

	ifstream cin("input");

	vector<string> str;
	string temp;

	while(cin>>temp)
	{
		for (unsigned int j = 0; j < temp.length(); j++)
		{
		    assert(((unsigned int)temp[j])>=((unsigned int)'a'));
		    assert(((unsigned int)temp[j])<=((unsigned int)'z'));
		}
		str.push_back(temp);
	}

	temp="";
	for(iter_t it = str.begin(); it != str.end(); ++it)
	{
	    cout<<it->size()<<" ";
	    temp += *it;
	}
	cout<<endl<<temp<<endl;

	SwapChar(&str[0],&str[1]);
	cout<<str[0]<<" "<<str[1]<<endl;
}
