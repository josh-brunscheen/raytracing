#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

//C++ std stuff
using std::make_shared;
using std::shared_ptr;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589793235;

//Utility
inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  //Random real in [0, 1)
  return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  //Random real in [min, max)
  return min + (max - min) * random_double();
}

//Common headers
// #include "color.h"
// #include "interval.h"
// #include "ray.h"
// #include "vec3.h"

#endif