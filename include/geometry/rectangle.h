#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "hittable.h"

class XYRect : public Hittable {
    public:
        XYRect() {}

        XYRect(double _x0, double _x1, double _y0, double _y1, double _k,
            const shared_ptr<Material>& mat)
            : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override {
            // The bounding box must have non-zero width in each dimension, so pad the Z
            // dimension a small amount.
            output_box = AABB(Point3(x0,y0, k-0.0001), Point3(x1, y1, k+0.0001));
            return true;
        }

    public:
        shared_ptr<Material> mp;
        double x0, x1, y0, y1, k;
};

#endif
