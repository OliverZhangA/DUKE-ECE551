unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else if (x == 0) {
    return 0;
  }
  return x * power(x, y - 1);
}
