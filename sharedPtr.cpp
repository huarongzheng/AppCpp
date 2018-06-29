#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<vector>
#include<iostream>
#include<time.h>
#include <algorithm>
#include <assert.h>
#include <memory>
#include <bits/stdc++.h>
using namespace std;



/*********************************************
 *  light weighted shared_ptr
 *  plz complete the "Fill me" section below
 *********************************************/


template <class T>
class SharedPtr;

/**
 * helper class that contains phyical ptr and ref count
 * feel free to just remove this helper and go directly
 * with SharedPtr implementation
 */
template <class T>
class RefPtr
{
    friend class SharedPtr<T>;
private:
     T *m_pPhyPtr;
     size_t m_RefCount;
     RefPtr(T *p);
     virtual ~RefPtr(); // why virtual here?
};

template <class T>
RefPtr<T>::RefPtr(T *p)
{
    // Fill me
    m_pPhyPtr = p;
    m_RefCount = 1;
    printf("RefPtr() ctor!\r\n");
}

template <class T>
RefPtr<T>::~RefPtr()
{
    // Fill me
    if (m_pPhyPtr)
    {
        printf("~RefPtr() destructor\n");
        delete m_pPhyPtr;
        m_RefCount =0;
    }
    m_pPhyPtr = NULL;
}



/**
 * a light smart pointer that allows 
 *     ctor with physical pointer
 *     *  return the value pointed by physical ptr
 *     -> return physcal ptr
 *     =  after op, both lhs rhs point to the same physical variable. the varible originally referred by lhs must be handled properly
 */
template <class T>
class SharedPtr
{
private:
    RefPtr<T> *m_pRef; // ref with count
public:
    SharedPtr();
    SharedPtr(T *p);
    //SharedPtr(SharedPtr<T>& other); // copy ctor
    ~SharedPtr();

    SharedPtr<T> & operator = (SharedPtr &other);
    T &operator *();
    T *operator ->();

    int use_count() {return m_pRef->m_RefCount;}
};

template <class T>
SharedPtr<T>::SharedPtr()
{
    m_pRef = NULL;
}

/**
 * ctor with physical pointer
 */
template<class T>
SharedPtr<T>::SharedPtr(T *p)
{
    // Fill me
    m_pRef = new RefPtr<T>(p);
    printf("SharedPtr(T *p) ctor\r\n");
}

/**
 * if this shared ptr is the last one referring to a variable, recollect physical resource
 */
template <class T>
SharedPtr<T>::~SharedPtr()
{
    // Fill me
    printf("~SharedPtr() destructor called\r\n");
    if (0 == (--m_pRef->m_RefCount))
    {
        printf("~SharedPtr() delete physical ptr\r\n");
        delete m_pRef;
        m_pRef = NULL;
    }
    if (m_pRef)
    {
        printf("~SharedPtr() current ref count=%d\n", m_pRef->m_RefCount);
    }
}

/*
 * after assignment, both lhs rhs point to the same physical variable.
 * the varible originally referred by lhs must be handled properly
 */
template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr &other)
{
    // Fill me
    // rls ref count +1  
    ++(other.m_pRef->m_RefCount);

    // left -1.  make sure it was pointing to another. !! if no there will be double free
    if (this->m_pRef)
    {
        if (--(this->m_pRef->m_RefCount) == 0)
        {
            delete this->m_pRef;
        }
    }

    this->m_pRef = other.m_pRef;
    return *this;
}

template <class T>
T &SharedPtr<T>::operator *()
{
    return *(m_pRef->m_pPhyPtr);
    printf("SharedPtr operator *() current ref count=%d\n", m_pRef->m_RefCount);
}

template <class T>
T *SharedPtr<T>::operator->()
{
    return (m_pRef->m_pPhyPtr);
}

//template <class T>
//SharedPtr<T>::SharedPtr(SharedPtr<T>& other)
//{
//    this->m_pRef = other.m_pRef;
//    ++(m_pRef->m_RefCount);
//    printf("SharedPtr(& other) copy ctor, current ref count=%d", this->m_pRef->m_RefCount);
//}

int main()
{
   SharedPtr<int>* pPtr = NULL;
   {
       SharedPtr<int> g_ptr;

       {
           SharedPtr<int> ptr1(new int(4));
           printf("test *ptr1=%d\n", *ptr1);
           // reassign to another
           g_ptr = ptr1;
       }
       printf("test *g_ptr=%d\n", *g_ptr);
       printf("test 4's ref count=%d\n", g_ptr.use_count());

       // new int(4) wasn't destroied coz there's another reference
       SharedPtr<int> ptr2(new int(3));
       // now reassign to ptr2
       g_ptr = ptr2;

       SharedPtr<int> *pPtr = &ptr2;
       printf("test **pPtr=%d\r\n", *(*pPtr));
    }

    sleep(2);
    //printf("%d\r\n", *(*pPtr));  
    return 0;
}


