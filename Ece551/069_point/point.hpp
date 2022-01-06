class Point {
 private:
  double x;
  double y;

 public:
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
  Point() : x(0), y(0) {}
};
