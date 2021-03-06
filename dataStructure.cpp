#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<vector>
#include<array>
#include<iostream>
#include<time.h>
#include<algorithm>
#include<typeinfo>

using namespace std;

template <class T>
class Node
{
public:
    Node(T in)
    {
        data = in;
        std::cout << "node ctor: " << data << std::endl;
    }
    virtual ~Node()
    {
        std::cout << "node dtor: " << data << std::endl;
    }

    T     data{};
    Node<T> *pNext{nullptr};
};

template <class T>
class List
{
public:
    static constexpr int ALL = std::numeric_limits<int>::max();
    List(const int &nLen)
    {
        m_pHead = new Node<T>(static_cast<T>(-1));
        pushFront(nLen);
        //pushBack(nLen);
    }
    virtual ~List()
    {
        remove(ALL);
    }
    void pushFront(const int &nLen)
    {
        Node<T> *pC;
        for (int i = 0; i < nLen; i++)
        {
            pC = new Node<T>(static_cast<T>(i));
            pC->pNext = m_pHead->pNext;
            m_pHead->pNext = pC;
        }
    }
    void pushBack(const int &nLen)
    {
        Node<T> *pC = m_pHead;
        for (int i = 0; i < nLen; i++)
        {
            pC->pNext = new Node<T>(static_cast<T>(i));
            pC       = pC->pNext;
        }
    }
    void remove(int num)
    {
        Node<T> *pC = m_pHead->pNext;
        while(nullptr != pC && num)
        {
            m_pHead->pNext = pC->pNext;
            delete pC;
            pC = m_pHead->pNext;
            if (ALL != num)
            {
                num--;
            }
        }
    }
    void reverse1()
    {
        Node<T> *pHead1 = new Node<T>(static_cast<T>(-2));
        Node<T> *pC = m_pHead->pNext;
        while(nullptr != m_pHead->pNext)
        {
            pC             = m_pHead->pNext;
            std::cout << "process node: " << pC->data << "  next: " << pC->pNext << std::endl;
            m_pHead->pNext = pC->pNext;
            pC->pNext      = pHead1->pNext;
            pHead1->pNext  = pC;
        }
        m_pHead->pNext = pHead1->pNext;
        delete pHead1;
    }
    void reverse2()
    {
        Node<T> *pHead1 = new Node<T>(static_cast<T>(-2));
        Node<T> *pC;
        while (nullptr != m_pHead->pNext)
        {
            // remove from old
            pC = m_pHead->pNext;
            m_pHead->pNext = pC->pNext;
            //std::cout << "remove node: " << pC->data << "  next: " << pC->pNext << std::endl;

            // insert to new
            pC->pNext = pHead1->pNext;
            pHead1->pNext = pC;
            //std::cout << "insert node: " << pM->data << "  next: " << pM->pNext << std::endl;
        }
        m_pHead->pNext = pHead1->pNext;
        delete pHead1;
    }
    void show(int num)
    {
        Node<T> *pC = m_pHead->pNext;
        while(nullptr != pC && num)
        {
            std::cout << "show node: " << pC->data << "  next: " << pC->pNext << std::endl;
            pC = pC->pNext;
            if (ALL == num)
            {
                num--;
            }
        }
    }

    Node<T> *m_pHead;
};

int main()
{
    List<int> myList(9);
    myList.show(List<int>::ALL);
    myList.reverse1();
    myList.show(List<int>::ALL);
    myList.reverse2();
    myList.show(List<int>::ALL);
    return 0;
}
