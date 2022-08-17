#ifndef AABB_H
#define AABB_H

#include "rtweekend.h"

class AABB {
    public:
        Point3 minimum, maximum;

    public:
        AABB() {}
        AABB(const Point3 &a, const Point3 &b) {
            minimum = a;
            maximum = b;
            for (int i = 0; i < 3; i ++)
                if (minimum[i] > maximum[i])
                    std::swap(minimum[i], maximum[i]);
        }

        bool hit(const Ray &r, double t_min, double t_max) const;
};

AABB surrounding_box(AABB box0, AABB box1);

#endif
