#include "aabb.h"

bool AABB::hit(const Ray &r, double t_min, double t_max) const {
    for (int i = 0; i < 3; i ++) {
        double inv = 1.0 / r.direction()[i];
        double t0 = (minimum[i] - r.origin()[i]) * inv;
        double t1 = (maximum[i] - r.origin()[i]) * inv;
        if (inv < 0)
            std::swap(t0, t1);
        t_min = t0 > t_min? t0: t_min;
        t_max = t1 < t_max? t1: t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

AABB surrounding_box(AABB box0, AABB box1) {
    Point3 a(fmin(box0.minimum[0], box1.minimum[0]),
            fmin(box0.minimum[1], box1.minimum[1]),
            fmin(box0.minimum[2], box1.minimum[2]));
    Point3 b(fmax(box0.maximum[0], box1.maximum[0]),
            fmax(box0.maximum[1], box1.maximum[1]),
            fmax(box0.maximum[2], box1.maximum[2]));
    return AABB(a, b);
}
