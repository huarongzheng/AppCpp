#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>
using namespace std;


#include <assert.h>
#include <vector>
#include <map>

#define LINE_LEN (200)
#define TOTAL_NUM (2)

typedef unsigned long u32_t;
typedef long s32_t;

class Server {
private:
	static int load;
public:
	static int compute(long long A, long long B) {
		load += 1;
		if(A < 0) {
			throw std::invalid_argument("A is negative");
		}
		vector<int> v(A, 0);
		int real = -1, cmplx = sqrt(-1);
		if(B == 0) throw 0;
		real = (A/B)*real;
		int ans = v.at(B);
		return real + A - B*ans;
	}
	static int getLoad() {
		return load;
	}
};
int Server::load = 0;

int main() {
	ifstream cin("input");

	int T; cin >> T;
	while(T--) {
		long long A, B;
		cin >> A >> B;
		/* Enter your code here. */
		Server server;
		int nResult;
		try
		{
			nResult = server.compute(A, B);
		}
		catch (bad_alloc &e)
		{
             cout << "Not enough memory" << endl;
             continue;
		}
		catch (exception &e)
		{
             cout << "Exception: " << e.what() << endl;
             continue;
		}
		catch (...)
		{
			cout << "Other Exception" << endl;
			continue;
		}

		cout << nResult << endl;
	}

	cout << Server::getLoad() << endl;
	return 0;
}
