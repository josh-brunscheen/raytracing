#ifndef COLOR_H
#define COLOR_H


#include "vec3.h"
#include "interval.h"

using color = vec3;

// void restrict(double& value, double min, double max) {
//   if (value < min) {
//     value = min;
//   } else if (value > max) {
//     value = max;
//   } 
// }

inline double linear_to_gamma(double linear_component) {
  if (linear_component > 0) return std::sqrt(linear_component);

  return 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  //Apply linear to gamma transform for gamma 2
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  //Translate [0,1] component vals to byte range [0,255]
  static const interval intensity(0.000, 0.999);
  int rbyte = int(255.999 * intensity.clamp(r));
  int gbyte = int(255.999 * intensity.clamp(g));
  int bbyte = int(255.999 * intensity.clamp(b));



  
  // restrict(r, 0.000, 0.999);
  // restrict(g, 0.000, 0.999);
  // restrict(b, 0.000, 0.999);

  // int rbyte = int(255.999 * r);
  // int gbyte = int(255.999 * g);
  // int bbyte = int(255.999 * b);

  //Write out pixel color
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif