#include <cstdio>
#include <iostream>

#include "bstmap.h"

int main() {
  BstMap<int, int> M;
  M.add(5, 6);
  M.add(7, 8);
  M.add(3, 4);
  M.add(1, 0);
  M.add(0, -1);
  M.add(4, 9);
  M.remove(3);
  M.remove(9);
  M.add(0, 0);
  M.add(0, 2);
  BstMap<int, int> n = M;
  M.add(3, 3);
  n = M;
  std::cout << n.lookup(5) << std::endl;
  std::cout << n.lookup(4) << std::endl;
  std::cout << n.lookup(7) << std::endl;
  std::cout << n.lookup(0) << std::endl;
  std::cout << n.lookup(1) << std::endl;
  std::cout << n.lookup(3) << std::endl;
  return EXIT_SUCCESS;
}
