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


class Workshop
{
public:
	Workshop()
    {
		m_nStart = 0;
		m_nDuration = 0;
		m_nEnd = 0;
    }

	~Workshop()
    {
    }

	string Show()
	{
		stringstream ss;
		ss << "(" <<  m_nStart << "\t"  <<  m_nEnd /*<< "\t" <<  m_nDuration */<< "\t)";
		return ss.str();
	}

	int m_nStart;
	int m_nDuration;
	int m_nEnd;
};

class Available_Workshops
{
public:
	Available_Workshops(int start_time[], int duration[], int n)
    {
		m_nSize = n;
		workshopArray = new Workshop[n];

		for (int i=0; i<m_nSize; i++)
		{
			workshopArray[i].m_nStart = start_time[i];
			workshopArray[i].m_nDuration = duration[i];
			workshopArray[i].m_nEnd = start_time[i]+duration[i]-1;
		}
    }

	~Available_Workshops()
    {
		delete [] workshopArray;
    }

	void Show() const
	{
		for (int i=0; i<m_nSize; i++)
		{
			cout << workshopArray[i].Show() << endl;
		}
	}

	Workshop *workshopArray;
	int m_nSize;
};

Available_Workshops* initialize (int start_time[], int duration[], int n)
{
	return (new Available_Workshops(start_time, duration, n));
}

bool Cmp(Workshop a, Workshop b)
{
	return a.m_nEnd < b.m_nEnd;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
	int nMaxIntervalCnt = 0;
	//int nSize = sizeof(ptr->workshopArray)/sizeof(ptr->workshopArray[0]);

	sort(ptr->workshopArray, (ptr->workshopArray)+ptr->m_nSize, Cmp);
    //ptr->Show();

	int nScheduleEnd = -1;
	for (int i=0; i<ptr->m_nSize; i++)
	{
		if (nScheduleEnd < (ptr->workshopArray)[i].m_nStart)
		{
		    nMaxIntervalCnt++;
		    nScheduleEnd = (ptr->workshopArray)[i].m_nEnd;
		}
	}

	return nMaxIntervalCnt;
}

int main(int argc, char *argv[]) {
	ifstream cin("input");
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}

