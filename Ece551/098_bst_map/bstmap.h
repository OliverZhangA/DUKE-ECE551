#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 public:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K _key, V _value, Node * _left = NULL, Node * _right = NULL) :
        key(_key),
        value(_value),
        left(_left),
        right(_right) {
      left = NULL;
      right = NULL;
    }
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  void copyhelper(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      copyhelper(current->left);
      copyhelper(current->right);
    }
  }
  BstMap(const BstMap & rhs) {
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
  ~BstMap() { destroy(root); }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap temp(rhs);
      Node * todestroy = root;
      root = temp.root;
      temp.root = todestroy;
    }
    return *this;
  }

  void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key == (*current)->key) {
        (*current)->value = value;
        return;
      }
      else if (key > (*current)->key) {
        current = &(*current)->right;
      }
      else {
        current = &(*current)->left;
      }
    }
    *current = new Node(key, value);
  }

  const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return current->value;
      }
      else if (current->key > key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("key not found!");
  }

  Node * findandremove(const K & toRemove, Node * current) {
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
        current->value = (*changenode)->value;
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
  void remove(const K & key) { root = findandremove(key, root); }
};
