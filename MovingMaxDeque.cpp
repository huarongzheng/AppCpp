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

void printKMax(int arr[], int n, int k){
    //Write your code here.

	deque<int> q;
    for (int i = 0; i < n; ++i)
    {
        if (!q.empty() && q.front() == i - k)
        {
        	q.pop_front();
        }
        while (!q.empty() && arr[q.back()] < arr[i])
        {
        	q.pop_back();
        }
        q.push_back(i);
        if (i >= k - 1)
        {
        	cout << arr[q.front()] << " ";
        }
    }
    cout << endl;
}
int main(){
    ifstream cin("input");

   int t;
   cin >> t;
   while(t>0) {
      int n,k;
       cin >> n >> k;
       int i;
       int arr[n];
       for(i=0;i<n;i++)
            cin >> arr[i];
       printKMax(arr, n, k);
       t--;
     }
     return 0;
}

