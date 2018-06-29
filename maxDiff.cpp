#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<vector>
#include<iostream>
#include<time.h>
#include <algorithm>
#include <assert.h>
#include <memory>
#include <bits/stdc++.h>
using namespace std;


/**********************************
You are given an array of integers and must compute the maximum difference between any item and any lower indexed smaller item for all the possible pairs, i.e., for a given array a find the maximum value of a[j] - a[i] for all i, j where 0 <= i < j < n and a[i] < a[j]. If there are no lower indexed smaller items for all the items, then return -1.

For example, given an array [ 1, 2, 6, 4], you would first compare 2 to the elements to its left.  1 is smaller, so calculate the difference 2 - 1 = 1.  6 is bigger than 2 and 1, so calculate the differences 4 and 5.  4 is only bigger than 2 and 1, and the differences are 2 and 3.  The largest difference was 6 - 1 = 5.

Function Description 
    Complete the function maxDifference in the "Fill me" section below. The function must return an integer representing the maximum difference in a.
maxDifference has the following parameter(s):
    a[a[0],a[1],...a[n-1]]:  an array of integers
Constraints
    1 <= n <= 10^5
    -10^6 <= a[i] <= 10^6

Sample Case 0
    Sample Input 0: 7 2 3 10 2 4 8 1
    Sample Output 8
Explanation
    n = 7, a = [2, 3, 10, 2, 4, 8, 1]
    Differences are calculated as:
    3 - [2] = [1]
    10 - [3, 2] = [7, 8]
    4 - [2, 3, 2] = [2, 1, 2]
    8 - [4, 2, 3, 2] = [4, 6, 5, 6]
    The maximum is found at 10 - 2 = 8.
*****************************/


int maxDifference(vector<int> a)
{
    //Fill me
    int nMaxDiff = a[1]-a[0];
    int nMin = a[0];
    int nTemp = nMaxDiff;
    for (int i=1; i<a.size(); i++)
    {
        nTemp = a[i]-nMin;
        cout << " min=" << nMin  << " a=" << a[i] << " diff=" << nTemp << " Max=" << nMaxDiff << endl;
        nMaxDiff = max(nMaxDiff, nTemp);
        if (a[i] < nMin)
        {
            nMin = a[i];
        }
    }

    return nMaxDiff;
}

int main()
{
    ofstream fout("output");
    ifstream cin("input");

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int i = 0; i < a_count; i++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[i] = a_item;
    }

    int res = maxDifference(a);

    fout << res << "\n";

    fout.close();

    return 0;
}

