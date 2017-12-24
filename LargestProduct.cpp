#include <bits/stdc++.h>
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
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef char data_t;

int main()
{
    ifstream cin("input");

    deque<data_t> q;
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++)
    {
        int n;
        int k;
        cin >> n >> k;
        string num;
        cin >> num;

        int long long nResult = 1, nMax = ~0;
        for (int i=0; i<(int)num.length(); i++)
        {

            if (i >= k)
            {
                data_t datapop = q.front();
                //cout << q.size() << "->";
                q.pop_front();
                //cout << q.size() << "  ";
                //cout << "out=" << (int)datapop << "  ";
                if (datapop == 0)
                {
                    nResult = 1;
                    for (deque<data_t>::iterator it=q.begin(); it!=q.end(); ++it)
                    {
                        nResult *= *it;
                    }
                }
                else
                {
                    nResult = nResult/datapop;
                }
            }

            data_t datain = data_t(num[i] - '0');
            nResult *= datain;
            q.push_back(datain);


            //cout << "in[" << i << "]=" << (int)datain << "/" << nResult << "\t\t";

            if (i >= k-1)
            {
                if (nMax < nResult)
                {
                    nMax = nResult;
                }
                //cout << "max: " << nMax << endl;
            }
        }

        cout << nMax << endl;
    }

    return 0;
}

#if 0

#include <bits/stdc++.h>
#include <fstream>
#include <string>

#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

template<class T>
inline void read(T &x) {
    char c;int f = 1;x = 0;
    while(((c=getchar()) < '0' || c > '9') && c != '-');
    if(c == '-') f = -1;else x = c-'0';
    while((c=getchar()) >= '0' && c <= '9') x = x*10+c-'0';
    x *= f;
}
static int outn;
static char out[(int)2e7];
template<class T>
inline void write(T x) {
    if(x < 0) out[outn++] = '-', x = -x;
    if(x) {
        static int tmpn;
        static char tmp[20];
        tmpn = 0;
        while(x) tmp[tmpn++] = x%10+'0', x /= 10;
        while(tmpn) out[outn++] = tmp[--tmpn];
    }
    else out[outn++] = '0';
}

const char s[] = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";


ll solve(int l, int r) {
    if(r - l + 1 < 13) return 0;
    ll cur = 1, ret = 0;
    for(int i = 0; i < 12; ++i)
        cur *= s[l + i] - '0';
    for(int i = l; i + 12 <= r; ++i) {
        cur *= s[i + 12] - '0';
        if(i > l) cur /= s[i - 1] - '0';
        chkmax(ret, cur);
    }
    return ret;
}


int main()
{
    ll ans = 0;
    int l = strlen(s);
    for(int i = 0; i < l; ++i)
        if(s[i] != '0') {
            int j = i;
            while(j < l - 1 && s[j + 1] != '0') ++j;
            chkmax(ans, solve(i, j));
            i = j;
        }
    std::cout << ans << std::endl;
    return 0;
}
#endif
