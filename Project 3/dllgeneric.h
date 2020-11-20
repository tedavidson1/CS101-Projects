#ifndef __DLL_H__
#define __DLL_H__

#include "exceptions.h"

template <typename T>
class DllNode {
public:
    T value;
    DllNode *prev;
    DllNode *next;
};

template <typename T>
class Dll {
public:
    Dll(){ //create empty list
      head = nullptr;
      tail = nullptr;
      listSize = 0;
    }
    Dll(const Dll &src); // create a deep copy of the src list
    Dll(const T arr[], int size); // create a linked list containing the elements of the array
    Dll &operator=(const Dll &src); // create a deep copy of the src list
    ~Dll(); // free all memory

    bool empty() const { // return if the list is empty in O(1)
      if (listSize == 0)  return true;
    }
    int size() const { // return how many items are in the list in O(1)
      return listSize;
    }

    T &at(int rank){ // return a reference to the value of the list at a rank/index
      //for (DllNode *cur = head; cur != NULL; cur = cur->next){}
    }
    void insert(int rank, T value){ // insert a value at the rank/index

    }
    T remove(int rank); // remove the node at the rank/index and return its value

    void clear(); // reset the list to an empty list
    void display(ostream &os) const; // write the contents of the list to the ostream

private:
  int listSize;
  DllNode* head;
  DllNode* tail;
};

template <typename T>
ostream &operator<<(ostream &os, const Dll<T> &list); // write the contents of the list to the ostream

#endif
