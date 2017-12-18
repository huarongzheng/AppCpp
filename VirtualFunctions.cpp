#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <assert.h>
#include <string.h>
#define MAX_LEN_NAME (101)
#define SUBJECT_NUM  (6)

class Person
{
public:
    Person ():
        age(0)
    {
        name = new char[MAX_LEN_NAME];
    }

    virtual ~Person()
    {
        delete [] name;
    }

    virtual void getdata() = 0;
    virtual void putdata() = 0;
protected:

    char *name;
    unsigned int age;

    void GetCommonData()
    {
        cin >> name;
        assert((strlen(name)>=1) && (strlen(name)<=100));
        cin >> age;
        assert((age>=1) && (age<=80));
    }

    void PutCommonData()
    {
        cout<<name<<" "<<age<<" ";
    }
};


class Professor: public Person
{
public:
    Professor():
        Person(),
        publications(0)
    {
        cur_id = ++g_uCurrId;
    }
    ~Professor()
    {
    }

    virtual void getdata()
    {
        GetCommonData();
        cin >> publications;
        assert((publications>=1) && (age<=1000));
    }

    virtual void putdata()
    {
        PutCommonData();
        cout<<publications<<" "<<cur_id<<endl;
    }

private:
    unsigned int publications;
    unsigned int cur_id;
    static unsigned int g_uCurrId;
};
unsigned int Professor::g_uCurrId=0;

class Student: public Person
{
public:
    Student():
        Person()
    {
        cur_id = ++g_uCurrId;
    }
    ~Student()
    {
    }

    virtual void getdata()
    {
        GetCommonData();
        for (int i=0; i<SUBJECT_NUM; i++)
        {
            try
            {
                cin>>marks[i];
                assert((marks[i]>=0) && (marks[i]<=100));
            }
            catch(...)
            {
                cout << "input marks error"<<endl;
                assert(0);
            }
        }
    }

    virtual void putdata()
    {
        PutCommonData();
        cout<<m_Sum(marks)<<" "<<cur_id<<endl;
    }

private:
    int m_Sum(const int marks[])
    {
        int uSum = 0;
        for (int i=0; i<SUBJECT_NUM; i++)
        {
            uSum += (*marks++);
        }
        return uSum;
    }
    int marks[SUBJECT_NUM];
    unsigned int cur_id;
    static unsigned int g_uCurrId;
};

unsigned int Student::g_uCurrId=0;

int main(){
	ifstream cin("input");

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
