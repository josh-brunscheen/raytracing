# raytracing
First attempt at a raytracing project in C++ with 3D graphing additions that I made.

I used the commands below for compiling, running, and then converting the produced image to a png.

First run this to compile everything:

```console
c++ main.cpp vec3.h color.h ray.h hittable.h hittable_list.h sphere.h camera.h interval.h rtweekend.h material.h grapher.h -o rt.exe
```

Direct the output to a .ppm image file (we will convert this later):
```console
./rt.exe > image.ppm
```

Then, finally, you can convert the output image into something like a .png:
```console
convert image.ppm tmp.png
```

Now, there should be file called "tmp.png" in the root folder. 


Sources:
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
