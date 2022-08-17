#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "Texture.h"

class SolidColor: public Texture {
    Color color;

    public:
        SolidColor() {}
        SolidColor(Color c): color(c) {}
        SolidColor(double r, double g, double b)
            : color(Color(r, g, b)) {}

        virtual Color value(double u, double v, const Point3& p) const override {
            return color;
        }
};

#endif
