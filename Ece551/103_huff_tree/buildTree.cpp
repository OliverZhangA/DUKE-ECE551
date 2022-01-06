#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t prq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      prq.push(new Node(i, counts[i]));
    }
  }
  while (prq.size() > 1) {
    Node * l = prq.top();
    prq.pop();
    Node * r = prq.top();
    prq.pop();
    prq.push(new Node(l, r));
  }
  return prq.top();
}
