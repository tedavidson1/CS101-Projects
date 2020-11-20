#ifndef __STACK_H__
#define __STACK_H__

#include "exceptions.h"
#include "dll.h"

template <typename T>
class Stack {
private:
    Dll<T> list;
public:
    Stack(){ // create an empty stack
    }
    void push(T value){ // add an item to the top of the stack
      list.insert(0, value);
    }
    T pop(){ // remove of the value at the top of the stack and return its value

      if (list.size() == 0){
        throw (InvalidOperationException("Stack empty"));
      }

      T x = list.remove(0);
      return x;
    }
    T peek(){ // return the value at the top of the stack, keeping it in the stack

      if (list.size() == 0){
        throw (InvalidOperationException("Stack empty"));
      }

      T x = list.at(0);
      return x;
    }

    int size() const{ // return how many items are in the stack
      return list.size();
    }

    bool empty() const{ // return if the stack is empty
      return list.empty();
    }

    void display(ostream &os) const{ // write the contents of the stack to the ostream
      list.display(os);
    }
};

template <typename T>
ostream &operator<<(ostream &os, const Stack<T> &stack){ // write the contents of the stack to the ostream
  stack.display(os);
  return os;
}
#endif
//dll.list;
//dll.insert(value);
