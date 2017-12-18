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

class Matrix
{
public:
	Matrix()
    {
    }

	virtual ~Matrix()
	{
	}

	void GetSize (int &n, int &m) const
	{
		n = a.size();
		assert(n != 0);
		m = a[0].size();
		assert(m != 0);
	}
/*
	void Show()
	{
		int n, m;
		GetSize(n, m);

	    for(int i=0;i<n;i++)
	    {
	        for(int j=0;j<m;j++)
	        {
	        	cout << a[i][j] << " ";
	        }
	        cout << endl;
	    }
	}
*/
	Matrix operator + (const Matrix & op)
	{
		Matrix result;
		int n,m, n2, m2;
		op.GetSize(n, m);
		//GetSize(n2, m2);

		//assert(n==n2);
		//assert(m==m2);

		result.a = op.a;
	    for(int i=0;i<n;i++)
	    {
	        for(int j=0;j<m;j++)
	        {
	        	result.a[i][j] = this->a[i][j] + op.a[i][j];
	        }
	    }

	    return result;
	}


	Matrix (const Matrix & that)
	{
		//int n, m;
		//that.GetSize(n, m);

		a = that.a;
	}

	Matrix & operator = (const Matrix & that)
	{
		int n,m ;
		that.GetSize(n, m);

		a = that.a;

	    return *this;
	}

	vector<vector<int>> a;
};

int main () {
   ifstream cin("input");
   int cases,k;
   cin >> cases;
   for(k=0;k<cases;k++) {
      Matrix x;
      Matrix y;
      Matrix result;
      int n,m,i,j;
      cin >> n >> m;
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         x.a.push_back(b);
      }
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         y.a.push_back(b);
      }
      result = x+y;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }
   }
   return 0;
}

