/* Project Checklist:
Deep Copy[]
Linked List from Array[x]
= Operator[]
Deconstructor[x]
Empty[x]
Size[x]
At[x]
Insert[x]
Remove[x]
Clear[x]
Display[]
os[x]
template[x]
*/

#ifndef __DLL_H__
#define __DLL_H__

#include "exceptions.h"
#include <iostream>

template <typename T>
class DllNode {
public:
    T value;
    DllNode *prev;
    DllNode *next;
};

template <typename T>
class Dll {

private:
  int listSize = 0;
  DllNode<T>* head;
  DllNode<T>* tail;

public:
    Dll(){ //create empty list
      //Dll List = new Dll;
      listSize = 0;
      head = NULL;
      tail = NULL;
    }

    Dll(const Dll &src){ // create a deep copy of the src list, same as =, DLL does't exist, so head and tail aren't null
      cout << "In copy constructor" << endl;
      head = NULL;
      tail = NULL;
      int i = 0;
      for (DllNode<T>* cur = src.head; cur != NULL; cur = cur->next, i++){
        T x = cur->value;
        insert(i, x);
      }
    }//end of deep copy

    Dll(const T arr[], int size){ // create a linked list containing the elements of the array
      head = NULL;
      tail = NULL;
      for (int i = 0; i < size; i++){
        insert(i, arr[i]);
      }
      //return arrayList;
    } //end of array to list

    Dll &operator=(const Dll &src){ // create a deep copy of the src list, left side can already exist, so clear it. then copy, call insert for each value
      cout << "In copy assignment" << endl;
      clear();
      head = NULL;
      tail = NULL;
      int  i = 0;
      for (DllNode<T>* cur = src.head; cur != NULL; cur = cur->next, i++){
        T x = cur->value;
        insert(i, x);
      }
      return *this;
    }//end copy assingment

    ~Dll(){ // free all memory,\just throw in a working clear
      //call clear, it removes all nodes but something else will remove the object
      clear();
    }

    bool empty() const { //return if the list is empty in O(1)
      if (listSize == 0){
        return true;
      }
      else{
        return false;
      }
    }

    int size() const { //return how many items are in the list in O(1)
      return listSize;
    } //end of size

    //template <typename T>
    T &at(int rank){ // return a reference to the value of the list at a rank/index

      if ((rank > listSize - 1) || (rank < 0)){
        throw (IndexOutOfRangeException("at(): Index was outside the bounds of the linked list.", rank));
      }

      int i = 0;
      DllNode<T>* cur = head;
      while (i != rank){
        cur = cur->next;
        i++;
      }
      return cur->value;
    }//end of at

    //template <typename T>
    void insert(int rank, T value){
      DllNode<T>* newNode = new DllNode<T>;
      newNode->value = value;
      DllNode<T>* cur = head;
      //cout << listSize << "and " << rank << endl;

      if ((rank > listSize) || (rank < 0)){ //deal with the logic later
        //cout << "in the if" << endl;
        throw (IndexOutOfRangeException("insert(): Index was outside the bounds of the linked list.", rank));
      }

      if (head == NULL){//if list is empty
        //make head = our new node, same with tail
        head = newNode;
        newNode->prev = NULL;
        tail = newNode;
        newNode->next = NULL;
        listSize++;
      }

      else if (rank == listSize){ // end of the list
        //make tail = to new node, make previous tail equal the new tail, make new tail point to null
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        newNode->next = NULL;
        listSize++;
      }

      else if (rank == 0){
        newNode->next = head;
        head = newNode;
        newNode->next->prev = newNode;
        newNode->prev = NULL;
        listSize++;
      }

      else{ //inserting between two nodes
        int i = 0;
        while (i != rank){
          cur = cur->next;
          i++;
        }
        //now cur is the rank
        DllNode<T>* old = cur->prev;
        old->next = newNode;
        newNode->prev = old;
        cur->prev = newNode;
        newNode->next = cur;
        listSize++;
      }
      return;
    }//end of function insert

    //template <typename T>
    T remove(int rank){ // remove the node at the rank/index and return its value

      if ((rank > listSize - 1) || (rank < 0)){
         throw (IndexOutOfRangeException("remove(): Index was outside the bounds of the linked list.", rank));
      }

      if (rank == 0 && listSize == 1){ //if list has one node
        DllNode<T>* cur = head;
        head = NULL;
        tail = NULL;
        T x = cur->value;
        delete cur;
        listSize--;
        return x;
      }

      else if (rank == 0){ //removing from the very front
        DllNode<T>* cur = head;
        head = cur->next;
        head->prev = NULL;
        T x = cur->value;
        delete cur;
        listSize--;
        return x;
      }

      else if (rank == (listSize - 1)){ //if it's the last node
        DllNode<T>* cur = tail;
        tail = cur->prev;
        cur->prev->next = NULL;
        T x = cur->value;
        delete cur;
        listSize--;
        return x;
      }

      else{//removing between two nodes
        int i = 0;
        DllNode<T>* cur = head;
        while (i != rank){
          cur = cur->next;
          i++;
        }
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        T x = cur->value;
        delete cur;
        listSize--;
        return x;
      }
    } //end of remove

    void clear(){ // reset the list to an empty list
      for (int i = listSize - 1; i >= 0; i--){
        remove(i);
      }
    }

    void display(ostream &os) const{ // write the contents of the list to the ostream
      os << "[ ";
      for (DllNode<T>* cur = head; cur != NULL; cur = cur->next){
        os << cur->value << " ";
      }
      os << "]";
}//end ostream

};

template <typename T>
ostream &operator<<(ostream &os, const Dll<T> &list){ // write the contents of the list to the ostream
    list.display(os);
    return os;
  }
#endif
