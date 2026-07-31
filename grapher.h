// Shapes to make:
// - plane
// - line
// - 2d wave functions
// - cube
// - 3d wave functions

#ifndef GRAPHER_H
#define GRAPHER_H

#include <vector>
#include "material.h"
#include "sphere.h"
#include "vec3.h"

using std::make_shared;
using std::shared_ptr;

double defaultFunc(double x, double y) {
    return 0.0; // Simple plane through the origin
}

class Grapher {
    public:
        const int defaultXSpacing = 1;
        const int defaultYSpacing = 1;

        const int defaultXMin = -2;
        const int defaultXMax = 2;
        const int defaultYMin = -2;
        const int defaultYMax = 2;

        Grapher() {
            mathFunc = defaultFunc; 

            xSpacing = defaultXSpacing;
            ySpacing = defaultYSpacing;

            xMin = defaultXMin;
            xMax = defaultXMax;

            yMin = defaultYMin;
            yMax = defaultYMax;

            // Defaults to random color
            auto albedo = color::random(0.5, 1);
            auto fuzz = 0.25;
            sphereMaterial = make_shared<metal>(albedo, fuzz);

            generatePoints();
        }

        Grapher(double (*f)(double, double), int xSpac, int ySpac, int xMinimum, int xMaximum,
                int yMinimum, int yMaximum, shared_ptr<material> material) {
            mathFunc = f;
            
            xSpacing = xSpac;
            ySpacing = ySpac;

            xMin = xMinimum;
            xMax = xMaximum;

            yMin = yMinimum;
            yMax = yMaximum;

            sphereMaterial = material;

            generatePoints();
        }

        std::vector<shared_ptr<sphere>> getPoints() {
            return points;
        }

    private:
        int xSpacing;
        int ySpacing;

        double (*mathFunc)(double, double);

        int xMin;
        int xMax;
        int yMin;
        int yMax;

        shared_ptr<material> sphereMaterial;

        std::vector<shared_ptr<sphere>> points;

        void generatePoints() {
            for (double x = xMin; x <= xMax; x += xSpacing) {
                for (double y = yMin; y <= yMax; y += ySpacing) {
                    double z = mathFunc(x, y);
                    point3 center(x, y, z);

                    // TODO: Allow user to change the size of the spheres
                    points.push_back(make_shared<sphere>(center, 0.5, sphereMaterial));
                }
            }
        }
};

#endif