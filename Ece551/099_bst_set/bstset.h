#include "set.h"
template<typename T>
class BstSet : public Set<T> {
 public:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(T _key, Node * _left = NULL, Node * _right = NULL) :
        key(_key),
        left(_left),
        right(_right) {
      left = NULL;
      right = NULL;
    }
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}
  void copyhelper(Node * current) {
    if (current != NULL) {
      add(current->key);
      copyhelper(current->left);
      copyhelper(current->right);
    }
  }
  BstSet(const BstSet & rhs) {
    root = NULL;
    copyhelper(rhs.root);
  }
  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }
  ~BstSet() { destroy(root); }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet temp(rhs);
      Node * todestroy = root;
      root = temp.root;
      temp.root = todestroy;
    }
    return *this;
  }

  void add(const T & key) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key == (*current)->key) {
        return;
      }
      else if (key > (*current)->key) {
        current = &(*current)->right;
      }
      else {
        current = &(*current)->left;
      }
    }
    *current = new Node(key);
  }

  bool contains(const T & key) const {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return true;
      }
      else if (current->key > key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  Node * findandremove(const T & toRemove, Node * current) {
    if (current == NULL) {
      return current;
    }
    else if (current->key == toRemove) {
      if (current->left == NULL) {
        Node * temp = current->right;
        delete current;
        return temp;
      }
      else if (current->right == NULL) {
        Node * temp = current->left;
        delete current;
        return temp;
      }
      else {
        Node ** changenode = &current->left;
        while ((*changenode)->right != NULL) {
          changenode = &(*changenode)->right;
        }
        current->key = (*changenode)->key;
        *changenode = findandremove((*changenode)->key, *changenode);
        return current;
      }
    }
    else {
      if (current->key > toRemove) {
        current->left = findandremove(toRemove, current->left);
      }
      else {
        current->right = findandremove(toRemove, current->right);
      }
    }
    return current;
  }
  void remove(const T & key) { root = findandremove(key, root); }
};
