#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "grapher.h"

#include <cmath>

double sineWave(double x, double y) {
  return std::sin(x) + std::sin(y);
}

int main() {
  hittable_list world;

  shared_ptr<material> sphereMaterial;
  auto albedo = color::random(0.5, 1);
  auto fuzz = 0.25;
  sphereMaterial = make_shared<metal>(albedo, fuzz);

  Grapher testFunction(sineWave, 2, 2, -3, 3, -3, 3, sphereMaterial);
  world.add(testFunction.getPoints());

  // vvv Camera settings (mess around them to experiment) vvv
  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1000; //Usually 1200
  cam.samples_per_pixel = 500;
  cam.max_depth = 20; //Usually 50

  cam.vfov = 20;
  cam.lookfrom = point3(0, 10, 20); //Usually point3(13, 2, 3);
  cam.lookat = point3(0, 0, 0);
  cam.vup = vec3(0, 1, 0);

  cam.defocus_angle = 0.6;
  cam.focus_dist = 22.3; //Usually 10.0


  // Create the scene :)
  cam.render(world);
}