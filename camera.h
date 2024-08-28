#ifndef CAMERA_H
#define CAMERA_H

// #include "rtweekend.h"

#include "hittable.h"
#include "color.h"
#include "material.h"

class camera {
  public:
    double aspect_ratio = 1.0; //Ratio of image w / h
    int image_width = 100; //Rendered image width in pix count
    int samples_per_pixel = 10; //Count of rand samples for each pixel
    int max_depth = 10; //Max number of ray bounces into scene

    double vfov = 90; //Vertical view angle (field of view)
    point3 lookfrom = point3(0, 0, 0); //Point cam is looking from
    point3 lookat = point3(0, 0, -1); //Point fam is looking at
    vec3 vup = vec3(0, 1, 0); //Cam-relative "up" direction

    double defocus_angle = 0; //Variation angle of rays through each pix
    double focus_dist = 10; //Distance from cam lookfrom to plane of perfect focus

    void render(const hittable& world) {
      initialize();

      std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

      for (int j = 0; j < image_height; j++) {
        std::clog << "\rScan lines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
          color pixel_color(0, 0, 0);
          for (int sample = 0; sample < samples_per_pixel; sample++) {
            ray r = get_ray(i, j);
            pixel_color += ray_color(r, max_depth, world);
          }
          write_color(std::cout, pixel_samples_scale * pixel_color);
        }
      }

      std::clog << "\rDone :)                  \n";
    }

  private:
    int image_height; //Rendered img height
    double pixel_samples_scale; //Col scale factor for sum of pix samples
    point3 center; // Cam center
    point3 pixel00_loc; //Loc of pixel 0, 0
    vec3 pixel_delta_u; // Offset to pixel to the right
    vec3 pixel_delta_v; //Offset to pixel below
    vec3 u, v, w; //Cam frame basis vectors
    vec3 defocus_disk_u; //Defocus disk horiz rad
    vec3 defocus_disk_v; //Defocus disk vert rad

    void initialize() {
      image_height = int(image_width / aspect_ratio);
      image_height = (image_height < 1) ? 1 : image_height;

      pixel_samples_scale = 1.0 / samples_per_pixel;

      center = lookfrom;

      //Det viewport dims
      auto theta = degrees_to_radians(vfov);
      auto h = std::tan(theta/2);
      auto viewport_height = 2.0 * h * focus_dist;
      auto viewport_width = viewport_height * (double(image_width) / image_height);
    
      //Calc u,v,w unit basis vector for cam coord frame
      w = unit_vector(lookfrom - lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);

      //Calc vecs across horizontal and down vertical viewport edges
      auto viewport_u = viewport_width * u; //Horiz edge
      auto viewport_v = viewport_height * -v; //Vert edge

      //Calc horizontal and verical delta vecs from pix to pix
      pixel_delta_u = viewport_u / image_width;
      pixel_delta_v= viewport_v / image_height;

      //Calc upper left pixel loc
      auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
      pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    
      //Calc cam defocus disk basis vectors
      auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
      defocus_disk_u = u * defocus_radius;
      defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int i, int j) const {
      //Construct cam ray from defocus disk and dir at a rand sampled point around pix loc i, j
      auto offset = sample_square();
      auto pixel_sample = pixel00_loc 
        + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);

      auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
      auto ray_direction = pixel_sample - ray_origin;

      return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
      //Ret vec to a rand point in the [-.5, -.5]-[.5, .5] unit sqaure
      return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 defocus_disk_sample() const {
      //Returns a rand point in the cam defocus disk
      auto p = random_in_unit_disk();
      return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
      if (depth <= 0) return color(0,0,0);

      hit_record rec;

      if (world.hit(r, interval(0.001, infinity), rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
          return attenuation * ray_color(scattered, depth - 1, world);

        return color(0, 0, 0);
      }

      vec3 unit_direction = unit_vector(r.direction());
      auto a = 0.5*(unit_direction.y() + 1.0);
      return (1.0 - a) * color(0.0, 0.0, 0.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif