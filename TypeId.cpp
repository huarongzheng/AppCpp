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
typedef long s32_t;


enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;

template <typename T> struct Traits
{
public:
	Traits()
    {

    }

	static string name(int nIndex)
	{
		string *typeString;
		int    ntypeSize;
		if (typeid(T) == typeid(Fruit))
		{
			ntypeSize = 3;
			typeString = fruitString;
		}
		else if (typeid(T) == typeid(Color))
		{
			ntypeSize = 3;
			typeString = colorString;
		}
		else
		{
			assert(0);
		}

		if (nIndex<ntypeSize && nIndex>=0)
		{
			return typeString[nIndex];
		}
		else
		{
			return "unknown";
		}
	}

	static string fruitString[3];
	static string colorString[3];

};

template<class T> string Traits<T>::fruitString[3] = {"apple", "orange", "pear"};
template<class T> string Traits<T>::colorString[3] = {"red", "green", "orange"};

int main()
{
	ifstream cin("input");
	int t = 0; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}


