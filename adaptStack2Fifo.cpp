#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stack>
#include<iostream>
#include<time.h>
#include<assert.h>
#include<memory>
using namespace std;

/**********************************************************************************
   provided std::stack with known public
      ctor/detor/push/pop/empty/size/top(snoop stack top value)

   use adapt pattern to come up with MyFifo, as in First In First Out
      with public ctor/detor/push/pop/size/empty/top(snoop first/next popped value)

***********************************************************************************/
#define STACK_NUM (2)
#define FRONT_STACK (0)
#define BACK_STACK  (1)

template <class T>
class MyFifo
{
public:
    MyFifo()
    {
    }

    virtual ~MyFifo()
    {
    }

    /**
     *  snoop front fifo value
     *  @return front value
     **/
    T top()
    {
        return stacks[FRONT_STACK].top();
    }


    /**
     *  pop front fifo value
     **/
    void pop()
    {
        stacks[FRONT_STACK].pop();
    }

    /**
     *  @param [in] val value to be pushed into fifo, should be fetched after all previous pushed values
     **/
    void push(T val)
    {
        while(!stacks[FRONT_STACK].empty())
        {
            stacks[BACK_STACK].push(stacks[FRONT_STACK].top());
            stacks[FRONT_STACK].pop();
        }
        if (!stacks[FRONT_STACK].empty())
        {
            assert(!"shouldn't be empty anymore");
        }

        stacks[FRONT_STACK].push(val);

        while(!stacks[BACK_STACK].empty())
        {
            stacks[FRONT_STACK].push(stacks[BACK_STACK].top());
            stacks[BACK_STACK].pop();
        }
        if (!stacks[BACK_STACK].empty())
        {
            assert(!"shouldn't be empty anymore");
        }
    }

    size_t size()
    {
        return stacks[FRONT_STACK].size();
    }

    bool empty()
    {
        return stacks[FRONT_STACK].empty();
    }

private:
    stack<int> stacks[STACK_NUM];
};

int main()
{
    const int nTestSize = 10;
    MyFifo<int> testFifo;

    for (int i = 0; i < nTestSize; i++)
    {
        testFifo.push(i);
    }

    cout << "after pushing size="<< testFifo.size() << " and empty="<< testFifo.empty() << "\n";

    while(!testFifo.empty())
    {
        cout << (int)testFifo.top() << "\n";
        testFifo.pop();
    }

    cout << "after poping size="<< testFifo.size() << " and empty="<< testFifo.empty() << "\n";
    return 0;
}

