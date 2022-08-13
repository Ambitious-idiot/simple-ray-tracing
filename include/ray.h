#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    Point3 orig;
    Vec3 dir;

    public:
        ray() {}
        ray(const Point3& origin, const Vec3& direction)
            : orig(origin), dir(direction)
        {}

        Point3 origin() const  { return orig; }
        Vec3 direction() const { return dir; }

        Point3 at(double t) const {
            return orig + t*dir;
        }
};

#endif