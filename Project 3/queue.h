#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "exceptions.h"
#include "dll.h"

template <typename T>
class Queue {

private:
  Dll<T> list;

public:
    Queue(){ // create an empty stack
    }

    void enqueue(T value){ // add an item to the front of the queue
      list.insert(list.size(), value);
    }

    T dequeue(){ // remove the value at the front of the queue and return its value

      if (list.size() == 0){
        throw (InvalidOperationException("Queue empty"));
      }

      return list.remove(0);
    }

    T peek(){ // return the value at the front of the queue, keeping it in the queue

      if (list.size() == 0){
        throw (InvalidOperationException("Queue empty"));
      }

      return list.at(0);
    }

    int size() const{ // return how many items are in the queue
      return list.size();
    }

    bool empty() const{ // return if the queue is empty
      return list.empty();
    }

    void display(ostream &os) const{ // write the contents of the queue to the ostream
      list.display(os);
    }
};

template <typename T>
ostream &operator<<(ostream &os, const Queue<T> &queue){ // write the contents of the queue to the ostream
  queue.display(os);
  return os;
}

#endif
