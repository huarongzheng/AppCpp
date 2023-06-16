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
    Node(T in) {
        data = in;
        std::cout << "ctor " << this << " data " << data << std::endl;
    }

    virtual ~Node() {
        std::cout << "dtor " << this << " data " << data << std::endl;
    }

    T data;
    Node<T> *pNext{nullptr};
};

template <class T>
void showNode(Node<T> *node) {
    std::cout << "current node value = " << node->data << std::endl;
}

template <class T>
class List
{
public:
    static constexpr int ALL = std::numeric_limits<int>::max();
    List(const int &nLen)
    {
        for (int i = 0; i< nLen; i++) {
            pushFront(i);
            //pushBack(i);
        }
    }
    virtual ~List()
    {
        remove();
    }
    void pushFront(T in)
    {
        pushFront(new Node<T>(in));
    }

    void pushFront(Node<T> *pI)
    {
        pI->pNext = pHead;
        pHead = pI;
    }

    void pushBack(T in)
    {
        pushBack(new Node<T>(in));
    }

    void pushBack(Node<T> *pI)
    {
        Node<T> *pC = pHead;
        Node<T> *pPrev;
        while (pC) {
            pPrev = pC;
            pC = pC->pNext;
        }
        if (pPrev) {
            pPrev->pNext = pI;
        } else {
            pHead = pI;
        }
    }

    int traverse (void (*cb)(Node<T> *), int num = ALL) {
        int i = 0;
        Node<T> *pC = pHead;
        while (pC && i < num) {
            cb(pC);
            pC = pC->pNext;
            i++;
        }
    }

    // remove num nodes
    int remove(int num = ALL)
    {
        Node<T> *pC;
        int i = 0;

        while (i< num && pHead) {
            pC = pHead;
            pHead = pHead->pNext;
            delete pC;
            i++;
        }
        return i;
    }

    void reverse1()
    {
        Node<T> *pHead1{nullptr};
        Node<T> *pC;

        std::cout << "reverse1" << std::endl;
        while (pHead) {
            pC = pHead;
            pHead = pHead->pNext;
            pC->pNext = pHead1;
            pHead1 = pC;
        }
        pHead = pHead1;
    }

    void reverse2()
    {
    }

    void show(int num = ALL)
    {
        traverse(showNode, num);
    }

    Node<T> *pHead{nullptr};
};

int main()
{
    List<int> myList(9);
    myList.show(List<int>::ALL);
    myList.reverse1();
    myList.show(List<int>::ALL);
    //myList.reverse2();
    //myList.show(List<int>::ALL);
    return 0;
}
