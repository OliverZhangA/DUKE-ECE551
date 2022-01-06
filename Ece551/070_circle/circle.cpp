#include "circle.hpp"

#include <cmath>
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
  return;
}
double Circle::intersectionArea(const Circle & otherCircle) {
  const double pi = 3.1415926535;
  double d = center.distanceFrom(otherCircle.center);
  if (d >= radius + otherCircle.radius) {
    return 0;
  }
  else if (d <= std::abs(radius - otherCircle.radius)) {
    return radius < otherCircle.radius ? pi * radius * radius
                                       : pi * otherCircle.radius * otherCircle.radius;
  }
  else {
    double angle1 =
        acos((radius * radius + d * d - otherCircle.radius * otherCircle.radius) /
             (2 * radius * d));
    double angle2 =
        acos((otherCircle.radius * otherCircle.radius + d * d - radius * radius) /
             (2 * otherCircle.radius * d));
    return radius * radius * angle1 + otherCircle.radius * otherCircle.radius * angle2 -
           d * radius * sin(angle1);
  }
}
