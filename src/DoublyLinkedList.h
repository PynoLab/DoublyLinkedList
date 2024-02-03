#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "Node.h"

template <class T>
class DoublyLinkedList
{
private:
  int64_t _size;
  Node<T> *head, *tail, *cursor;
  int64_t cursorPosition;
  bool circular;

  void detach(Node<T> *node)
  {
    if (node->getPrev())
      node->getPrev()->setNext(node->getNext());
    if (node->getNext())
      node->getNext()->setPrev(node->getPrev());
  }

  int64_t calcTo(const int64_t index) const
  {
    if (index < -_size - 2 || index >= _size)
      return -1;
    return index >= 0 ? index : _size + index;
  }

  Node<T> *getNodeAt(const int64_t index) const
  {
    if (index < 0)
      return nullptr;

    Node<T> *tmp = cursor;
    int8_t step = cursorPosition < index ? 1 : -1;

    for (int64_t i = cursorPosition; i != index; i += step)
      tmp = step > 0 ? tmp->getNext() : tmp->getPrev();

    return tmp;
  }

public:
  DoublyLinkedList(bool circular = false) : circular(circular)
  {
    head = tail = cursor = nullptr;
    _size = 0;
    cursorPosition = -1;
  }

  ~DoublyLinkedList()
  {
    clear();
  }

  void setIsCircular(bool value)
  {
    circular = value;
    if (value && _size > 1)
    {
      head->setPrev(tail);
      tail->setNext(head);
    }

    else if (!value && _size > 1)
    {
      head->setPrev(nullptr);
      tail->setNext(nullptr);
    }
  }

  void insert(const T value, int64_t index)
  {
    const int64_t to = calcTo(index);

    if (to < 0 && to != 0)
      return;

    Node<T> *tmp = getNodeAt(to);
    Node<T> *node = new Node<T>(value);

    if (tmp->getPrev())
    {
      tmp->getPrev()->setNext(node);
      node->setPrev(tmp->getPrev());
    }
    tmp->setPrev(node);
    node->setNext(tmp);
    if (to == cursorPosition)
      cursorPosition++;
    if (to == 0)
      head = node;
    _size++;

    if (circular && _size > 1)
    {
      tail->setNext(head);
      head->setPrev(tail);
    }
  }

  void insert(const T value)
  {

    Node<T> *node = new Node<T>(value);
    if (!_size)
    {
      head = tail = cursor = node;
      cursorPosition = 0;
    }
    else
    {
      tail->setNext(node);
      node->setPrev(tail);
      tail = node;
    }
    _size++;
    if (circular && _size > 1)
    {
      tail->setNext(head);
      head->setPrev(tail);
    }
  }

  int64_t size() const
  {
    return _size;
  }

  void removeAt(int64_t index)
  {
    const int64_t to = calcTo(index);

    if (to < 0)
      return;

    Node<T> *tmp = getNodeAt(to);
    if (cursorPosition == to)
    {
      if (cursor->getNext() && cursor != tail)
        cursor = cursor->getNext();
      else
      {
        cursor = cursor->getPrev();
        cursorPosition--;
      }
    }

    else if (cursorPosition > to)
      cursorPosition--;

    if (tmp == head)
      head = head->getNext();

    else if (tmp == tail)
      tail = tail->getPrev();

    detach(tmp);
    _size--;

    if (!_size)
      cursorPosition = -1;
    delete tmp;
  }

  void remove(T value)
  {
    const int64_t i = indexOf(value);
    if (i > -1)
      removeAt(i);
  }

  int64_t indexOf(T value) const
  {

    const Node<T> *tmp = head;
    for (int64_t i = 0; i < _size; i++)
    {
      if (tmp->getValue() == value)
        return i;
      tmp = tmp->getNext();
    }
    return -1;
  }

  void set(int64_t index, T value)
  {
    const int64_t to = calcTo(index);
    if (to < 0)
      return;
    getNodeAt(to)->setValue(value);
  }

  T pop()
  {
    T value = tail->getValue();
    removeAt(-1);
    return value;
  }

  T getCursorValue() const
  {
    return cursor->getValue();
  }

  int64_t getCursorPosition() const
  {
    return cursorPosition;
  }

  void shiftCursor(const int64_t offset)
  {
    int64_t _offset = abs(offset % _size);

    for (int64_t i = 0; i < _offset; i++)
      cursor = offset > 0 ? cursor->getNext() : cursor->getPrev();

    cursorPosition += _offset;
  }

  void setCursorAt(const int64_t pos)
  {
    int64_t to = calcTo(pos);
    if (to < 0)
      return;
    cursor = getNodeAt(to);
    cursorPosition = to;
  }

  void clear()
  {
    Node<T> *current = head;
    if(circular)
      tail->setNext(nullptr);
    while (current)
    {
      Node<T> *nextNode = current->getNext();
      delete current;
      current = nextNode;
    }

    _size = 0;
    cursorPosition = -1;
    head = tail = cursor = nullptr;
  }

  DoublyLinkedList<T> filter(bool (*func)(T))
  {
    DoublyLinkedList<T> newList;
    Node<T> *tmp = head;
    for (int64_t i = 0; i < _size; i++)
    {
      if (func(tmp->getValue()))
        newList.insert(tmp->getValue());
      tmp = tmp->getNext();
    }
    return newList;
  }

  void foreach (void (*func)(T)) const
  {
    Node<T> *tmp = head;
    for (int64_t i = 0; i < _size; i++)
    {
      func(tmp->getValue());
      tmp = tmp->getNext();
    }
  }

  DoublyLinkedList<T> map(T (*func)(T)) const
  {
    DoublyLinkedList<T> newList;
    Node<T> *tmp = head;
    for (int64_t i = 0; i < _size; i++)
    {
      newList.insert(func(tmp->getValue()));
      tmp = tmp->getNext();
    }

    return newList;
  }

  DoublyLinkedList<T> &operator+=(const DoublyLinkedList<T> &rhs) 
  {

    for (int i = 0; i < rhs.size(); i++)
      this->insert(rhs[i]);
    return *this;
  }

  T operator[](const int64_t index) const
  {
    return getNodeAt(calcTo(index))->getValue();
  }
};

#endif