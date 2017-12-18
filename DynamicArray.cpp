#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <assert.h>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>

#define INIT_VAL (0)
#define RANGE_UNIT (100000) //1e5
typedef unsigned long u32_t;
typedef long s32_t;
typedef vector<vector<u32_t> *> vectorpt_t;

int main(){

    //ifstream cin("input");

    u32_t n, q, k;
    u32_t val;
    cin>>n>>q; //array and query
    assert((n>=1) && (n<=RANGE_UNIT));
    assert((q>=1) && (q<=RANGE_UNIT));

    vectorpt_t arrayDim1(n,NULL);

    // get input array
    for(u32_t i = 0;i < n;i++)
    {
        cin>>k;
        assert((k>=1) && (k<=3*RANGE_UNIT));
        arrayDim1[i] = new vector<u32_t>(k,INIT_VAL);
        for (u32_t j = 0; j < k; j++)
        {
            try
            {
                cin>>val;
                (*arrayDim1[i])[j] = val;
            }
            catch(...)
            {
                assert(0);
                cout<<"input error!"<<endl;
            }
        }
    }

    //query array
    for(u32_t i = 0;i < q;i++)
    {
        s32_t uQueryx,uQueryy;
        cin>>uQueryx>>uQueryy;
        assert((uQueryx>=0) && (((u32_t)uQueryx)<n));
        assert((uQueryy>=0) && (((u32_t)uQueryy)<(*arrayDim1[uQueryx]).size()));

        cout<<(*arrayDim1[uQueryx])[uQueryy]<<endl;
    }

    // destruct array
    for(u32_t i=0;i<n;i++)
    {
        delete arrayDim1[i];
    }

    return 0;

}
