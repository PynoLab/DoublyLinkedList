#ifndef Node_h
#define Node_h

#include <Arduino.h>

template <class T>
class Node
{
private:
  Node<T> *prev, *next;
  T value;

public:
  Node(T value)
  {
    prev = next = nullptr;
    this->value = value;
  }

  ~Node()
  {
    prev = next = nullptr;
    delete prev;
    delete next;
  }

  void setPrev(Node *prev)
  {
    this->prev = prev;
  }

  void setNext(Node *next)
  {
    this->next = next;
  }

  void setValue(const T value)
  {
    this->value = value;
  }

  Node<T> *getNext() const
  {
    return next;
  }

  Node<T> *getPrev() const
  {
    return prev;
  }

  T getValue() const
  {
    return value;
  }
};
#endif