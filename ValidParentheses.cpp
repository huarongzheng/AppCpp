#include <bits/stdc++.h>
#include <stack>
#include <string>
#include <cstdio>

using namespace std;

bool IsValid(string s)
{
    stack<char> stk;
    char c;
    for (size_t i=0; i<s.size(); i++)
    {
        c = s[i];
        if (c == '(')
        {
            stk.push(')');
        }
        else if (c == '{')
        {
            stk.push('}');
        }
        else if (c == '[')
        {
            stk.push(']');
        }
        else if (stk.empty() || stk.top() != c)
        {
            stk.pop();
            return false;
        }
        else
        {
            stk.pop();
        }

    }
    return stk.empty();
}

int main() {

    ifstream cin("input");

    string cmd;

    while (getline(cin,cmd))
    {
        bool bIsValid = IsValid(cmd);
        cout << "parentheses " << bIsValid  << endl;
    }


}
