#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
class Tester;
class noFoundExcp : public std::exception {
  const char * msg;

 public:
  explicit noFoundExcp(const char * msg_) : msg(msg_) {}
  virtual const char * what() const throw() { return msg; }
};

template<typename T>
class LinkedList {
 public:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : next(NULL), prev(NULL){};
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL){};
  LinkedList(const LinkedList & rhs) {
    if (rhs.head == NULL) {
      head = NULL;
      tail = NULL;
      return;
    }
    else {
      head = NULL;
      tail = NULL;
      Node * curr = rhs.head;
      while (curr != NULL) {
        T a = curr->data;
        this->addBack(a);
        curr = curr->next;
      }
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList temp(rhs);
    Node * headtemp = head;
    Node * tailtemp = tail;
    head = temp.head;
    tail = temp.tail;
    temp.head = headtemp;
    temp.tail = tailtemp;
    return *this;
  }
  ~LinkedList() {
    while (head != NULL) {
      if (head == tail) {
        tail = NULL;
      }
      Node * temp = head;
      head = head->next;
      delete temp;
    }
  }
  void addFront(const T & item) {
    if (head == NULL && tail == NULL) {
      head = new Node(item, NULL, NULL);
      tail = head;
      return;
    }
    head->prev = new Node(item, head, NULL);
    head = head->prev;
  }
  void addBack(const T & item) {
    if (head == NULL && tail == NULL) {
      head = new Node(item, NULL, NULL);
      tail = head;
      return;
    }
    else {
      Node * temp = new Node(item, NULL, tail);
      tail->next = temp;
      tail = temp;
    }
  }
  bool remove(const T & item) {
    Node ** curr = &head;
    while (*curr != NULL) {
      if ((*curr)->data == item) {
        // 	if(*curr == tail && *curr == head) {
        // 	  delete head;
        // 	  head = NULL;
        // 	  tail = NULL;
        // 	  return true;
        // 	} else if (*curr == tail) {}
        if (*curr == tail) {
          if (*curr == head) {
            delete head;
            head = NULL;
            tail = NULL;
            return true;
          }
          else {
            *curr = NULL;
            Node * temp = tail;
            tail = tail->prev;
            delete temp;
            return true;
          }
        }
        Node * temp = *curr;
        *curr = (*curr)->next;
        if (*curr != NULL) {
          (*curr)->prev = temp->prev;
        }
        else {
          tail = NULL;
        }
        delete temp;
        return true;
      }
      curr = &(*curr)->next;
    }
    return false;
  }

  T & operator[](int index) {
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      if (curr == NULL) {
        throw noFoundExcp("item not found!");
      }
      curr = curr->next;
    }
    return curr->data;
  }
  const T & operator[](int index) const {
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      if (curr == NULL) {
        throw noFoundExcp("item not found!");
      }
      curr = curr->next;
    }
    return curr->data;
  }

  int find(const T & item) {
    Node * curr = head;
    int index = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      index++;
      curr = curr->next;
    }
    return -1;
  }
  int getSize() const {
    int size = 0;
    Node * curr = head;
    while (curr != NULL) {
      size++;
      curr = curr->next;
    }
    return size;
  }
  friend class Tester;
};

#endif
