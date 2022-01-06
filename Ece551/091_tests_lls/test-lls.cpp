#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList i2;
    i2.addFront(2);
    i2.addFront(1);
    assert(i2[0] == 1);
    assert(i2[1] == 2);
    assert(i2.tail->data == 2);
    assert(i2.head->data == 1);
    assert(i2.tail->prev->data == 1);
    assert(i2.head->next->data == 2);
  }
  void testAddBack() {
    IntList i3;
    i3.addBack(1);
    i3.addBack(2);
    assert(i3[0] == 1);
    assert(i3[1] == 2);
    assert(i3.tail->data == 2);
    assert(i3.head->data == 1);
    assert(i3.tail->prev->data == 1);
    assert(i3.head->next->data == 2);
  }
  void testDestructor() {
    IntList i3;
    i3.addBack(1);
    i3.addBack(2);
    i3.remove(2);
    assert(i3.getSize() == 1);
    assert(i3.tail->next == NULL);
  }
  void testCopyConstructor() {
    IntList i3;
    i3.addBack(1);
    i3.addBack(2);
    IntList il(i3);
    assert(il[0] == 1);
    assert(il[1] == 2);
    assert(il.tail->data == 2);
    assert(il.head->data == 1);
    assert(il.tail->prev->data == 1);
    assert(il.head->next->data == 2);
    assert(il.getSize() == 2);
  }
  void testCopyAssignment() {
    IntList i3;
    i3.addBack(1);
    i3.addBack(2);
    IntList il;
    il.addBack(3);
    il.addBack(5);
    il.addBack(4);
    il = i3;
    assert(il[0] == 1);
    assert(il[1] == 2);
    assert(il.tail->data == 2);
    assert(il.head->data == 1);
    assert(il.tail->prev->data == 1);
    assert(il.head->next->data == 2);
    assert(il.head != i3.head);
    assert(il.tail != i3.tail);
    i3.addBack(9);
    assert(il.getSize() == 2);
    IntList i4;
    i4.addBack(3);
    i4.addBack(8);
    IntList i5;
    i4 = i5;
    assert(i4.head == NULL);
    assert(i4.tail == NULL);
    // IntList i2;
    // i2.addBack(3);
    // i2 = i3;
    // assert(i2[0] == 1);
    // assert(i2[1] == 2);
    // assert(i2.tail->data == 2);
    // assert(i2.head->data == 1);
    // assert(i2.tail->prev->data == 1);
    // assert(i2.head->next->data == 2);
  }
  void testRemove() {
    IntList i3;
    i3.addFront(2);
    i3.addFront(1);
    i3.remove(1);
    assert(i3.head->data == 2);
    assert(i3.head->prev == NULL);
    assert(i3.head->next == NULL);
    assert(i3.tail->data == 2);
    assert(i3.tail->next == NULL);
    assert(i3.tail->prev == NULL);
    assert(i3.getSize() == 1);

    i3.addFront(1);
    i3.remove(2);
    assert(i3.head->data == 1);
    assert(i3.head->prev == NULL);
    assert(i3.head->next == NULL);
    assert(i3.tail->data == 1);
    assert(i3.getSize() == 1);

    i3.addFront(3);
    i3.addFront(5);
    i3.remove(3);
    assert(i3.head->data == 5);
    assert(i3.head->prev == NULL);
    assert(i3.head->next->data == 1);
    assert(i3.tail->prev->data == 5);
    assert(i3.tail->next == NULL);
    assert(i3[1] == 1);
    assert(i3.tail->data == 1);
    assert(i3.getSize() == 2);

    IntList i2;
    i2.addFront(2);
    i2.addFront(1);
    i2.addFront(3);
    i2.remove(3);
    i2.addBack(9);
    i2.remove(9);
    assert(!i2.remove(7));
    assert(i2[0] == 1);
    assert(i2[1] == 2);
    assert(i2.tail->data == 2);
    assert(i2.head->data == 1);
    assert(i2.tail->prev->data == 1);
    assert(i2.head->next->data == 2);
    i2.remove(1);
    i2.remove(2);
    assert(i2.head == NULL);
    assert(i2.tail == NULL);
  }
  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopyConstructor();
  t.testDestructor();
  t.testCopyAssignment();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
