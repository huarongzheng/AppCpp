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
#define INVALID_NODE (-1)

typedef unsigned long u32_t;
typedef long s32_t;

struct Node{
   Node *prev;
   Node *next;
   int key;
   int value;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){nNodeNum++; assert(nNodeNum<=644);};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){nNodeNum++; assert(nNodeNum<=644);};
   static int nNodeNum;
};

int Node::nNodeNum = 0;

class Cache{
   protected:
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache: public Cache
{
public:
    LRUCache (int capacity)
    {
        cp = capacity;
        Node *curr = NULL;
        for (int i = 0; i < capacity; i++)
        {
            if (curr == NULL)
            {
                curr = new Node(INVALID_NODE, INVALID_NODE);
                head = curr;
            }
            else
            {
                curr -> next = new Node(curr, NULL, INVALID_NODE, INVALID_NODE);
                curr = curr -> next;
            }

            if (i == capacity - 1)
            {
                tail = curr;
            }
        }
    }

    virtual ~LRUCache ()
    {
        for (Node *curr = head; curr -> next != NULL; )
        {
            Node *temp = curr -> next;
            delete curr;
            curr = temp;
        }
    }

    virtual void set(int nKey, int nVal)
    {
        bool bHit = false;
        assert(nKey >= 1 && nKey <= 20 );
        assert(nVal >= 1 && nVal <= 2000 );
        if (mp.find(nKey) == mp.end())
        {
            bHit = false;
            //remove tail key
            if (tail->key != INVALID_NODE)
            {
                assert(mp.find(tail->key) != mp.end());
                mp.erase(mp.find(tail->key));
            }

            mp[nKey] = tail;
            //PushFront(new Node(nKey, nVal));
            mp[nKey] -> key = nKey;
            mp[nKey] -> value = nVal;
            DeleteNode(mp[nKey]);
            PushFront(mp[nKey]);
        }
        else
        {
            bHit = true;
            mp[nKey] -> key = nKey;
            mp[nKey] -> value = nVal;
            DeleteNode(mp[nKey]);
            PushFront(mp[nKey]);
        }
        //cout << "map size " << mp.size() << " hit " << bHit << endl;
    }

    virtual int get(int nKey)
    {
        int nResult = INVALID_NODE;
        if (mp.find(nKey) == mp.end())
        {
            nResult = INVALID_NODE;
        }
        else
        {
            nResult = mp[nKey]->value;
            DeleteNode(mp[nKey]);
            PushFront(mp[nKey]);
        }
        return nResult;
    }

private:

    void PushFront(Node *pNodeNew)
    {
        pNodeNew -> next = head;
        pNodeNew -> prev = NULL;

        if (pNodeNew -> next)
        {
            pNodeNew -> next -> prev = pNodeNew;
        }
        else
        {
            tail = pNodeNew;
        }

        head = pNodeNew;
    }

    void InsertAfter(Node *pNode, Node *pNodeNew)
    {
        assert(pNodeNew != NULL);
        pNodeNew -> next = pNode -> next;
        pNodeNew -> prev = pNode;

        if (pNodeNew -> next)
        {
            pNode -> next -> prev = pNodeNew;
        }
        else
        {
            tail = pNodeNew;
        }
        pNode -> next = pNodeNew;
    }

    void DeleteNode(Node *pNode)
    {
        assert (pNode);
        if (pNode -> prev)
        {
            pNode -> prev -> next = pNode -> next;
        }
        else
        {
            assert (pNode == head);
            head = pNode -> next;
        }

        if (pNode -> next)
        {
            pNode -> next -> prev = pNode -> prev;
        }
        else
        {
            assert (pNode == tail);
            tail = pNode -> prev;
        }

        //delete pNode;
        //pNode = NULL;
    }
};

int main() {
    ifstream cin("input");
    int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}

