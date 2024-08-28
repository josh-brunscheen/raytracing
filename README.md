# raytracing
First attempt at a raytracing project in C++.

NOTE: This project was meant to be more of a robust attempt at getting started with raytracing.
That being said, I did not use CMake, but I recommend that you should.

ANOTHER NOTE: This project closely follows the book "Ray Tracing in One Weekend" (cited below), with some minor deviations in terms of setting up and running this code.

I used the commands below for compiling, running, and then converting the produced image to a png.

First run this:

```console
c++ main.cpp vec3.h color.h ray.h hittable.h hittable_list.h sphere.h camera.h interval.h rtweekend.h material.h -o rt.exe
```

Then this:
```console
./rt.exe > image.ppm
```

Then, finally, this:
```console
convert image.ppm tmp.png
```

Now, there should be file called "tmp.png" in the root folder. (pngs are usually more accesible to view)


Sources:
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
