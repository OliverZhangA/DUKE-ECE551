#include <cstdio>
#include <iostream>

#include "bstset.h"

int main() {
  BstSet<int> M;
  M.add(5);
  M.add(7);
  M.add(3);
  M.add(1);
  M.add(0);
  M.add(4);
  M.remove(3);
  M.remove(9);
  M.add(0);
  M.add(0);
  BstSet<int> n = M;
  M.add(3);
  n = M;
  n.add(3);
  n.add(3);
  n.remove(3);
  std::cout << n.contains(5) << std::endl;
  std::cout << n.contains(4) << std::endl;
  std::cout << n.contains(7) << std::endl;
  std::cout << n.contains(0) << std::endl;
  std::cout << n.contains(1) << std::endl;
  std::cout << n.contains(3) << std::endl;
  return EXIT_SUCCESS;
}
