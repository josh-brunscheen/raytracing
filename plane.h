// Shapes to make:
// - plane
// - line
// - 2d wave functions
// - cube
// - 3d wave functions

#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "material.h"
#include "sphere.h"
#include "vec3.h"

using std::make_shared;
using std::shared_ptr;

class Plane {
    public:
        const int defaultXSpacing = 2;
        const int defaultYSpacing = 2;

        const int defaultXMin = -10;
        const int defaultXMax = 10;
        const int defaultYMin = -10;
        const int defaultYMax = 10;

        Plane() {
            a = 0;
            b = 0;
            c = 1;
            d = 0;
            xSpacing = defaultXSpacing;
            ySpacing = defaultYSpacing;

            xMin = defaultXMin;
            xMax = defaultXMax;

            yMin = defaultYMin;
            yMax = defaultYMax;

            generatePoints();
        }

        // Plane(int A, int B, int C, int D) : 
        //     a(A), b(B), c(C), d(D),
        //     xSpacing(defaultXSpacing), ySpacing(defaultYSpacing),
        //     xMin(defaultXMin), xMax(defaultXMax),
        //     yMin(defaultYMin), yMax(defaultYMax)
        // {
        //     generatePoints();
        // } 

        std::vector<shared_ptr<sphere>> getPoints() {
            return points;
        }

    private:
        int a;
        int b;
        int c;
        int d;

        int xSpacing;
        int ySpacing;

        int xMin;
        int xMax;
        int yMin;
        int yMax;

        std::vector<shared_ptr<sphere>> points;

        void generatePoints() {
            for (int x = xMin; x <= xMax; x += xSpacing) {
                for (int y = yMin; y <= yMax; y += ySpacing) {
                    double z = ((-a / c)*x) - ((b / c)*y) - (d/c);
                    point3 center(x, y, z);

                    // Currently just supports metal material
                    shared_ptr<material> sphereMaterial;
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = 0.25;
                    sphereMaterial = make_shared<metal>(albedo, fuzz);

                    points.push_back(make_shared<sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
};

#endif