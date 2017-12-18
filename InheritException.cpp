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
#include <bits/stdc++.h>

#define INIT_VAL (0)
#define RANGE_UNIT (100000)
typedef unsigned long u32_t;
typedef long s32_t;
//typedef vector<vector<u32_t> *> vectorpt_t;


class BadLengthException
{
public:
	BadLengthException(int n)
    {
		m_nLen = n;
    }

	virtual ~BadLengthException()
	{
	}

	int what()
	{
		return m_nLen;
	}

private:
	int m_nLen;
};


bool checkUsername(string username) {
	bool isValid = true;
	int n = username.length();
	if(n < 5) {
		throw BadLengthException(n);
	}
	for(int i = 0; i < n-1; i++) {
		if(username[i] == 'w' && username[i+1] == 'w') {
			isValid = false;
		}
	}
	return isValid;
}

int main() {

	ifstream cin("input");

	int T; cin >> T;
	while(T--) {
		string username;
		cin >> username;
		try {
			bool isValid = checkUsername(username);
			if(isValid) {
				cout << "Valid" << '\n';
			} else {
				cout << "Invalid" << '\n';
			}
		} catch (BadLengthException e) {
			cout << "Too short: " << e.what() << '\n';
		}
	}
	return 0;
}
