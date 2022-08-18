#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "hittable.h"

class AARect: public Hittable {
    shared_ptr<Material> mat_ptr;
    double a[4], k;
    int axis;

    public:
        AARect() {}
        AARect(double _a0, double _a1, double _b0, double _b1, double _k,
            const shared_ptr<Material>& mat, int ax)
            : a{_a0, _a1, _b0, _b1}, k(_k), mat_ptr(mat), axis(ax) {};

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;
};

class XYRect: public AARect {
    public:
        XYRect() {}
        XYRect(double x0, double x1, double y0, double y1, double k,
            const shared_ptr<Material>& mat)
            : AARect(x0, x1, y0, y1, k, mat, 2) {};
};

class YZRect: public AARect {
    public:
        YZRect() {}
        YZRect(double y0, double y1, double z0, double z1, double k,
            const shared_ptr<Material>& mat)
            : AARect(y0, y1, z0, z1, k, mat, 0) {};
};

class XZRect: public AARect {
    public:
        XZRect() {}
        XZRect(double x0, double x1, double z0, double z1, double k,
            const shared_ptr<Material>& mat)
            : AARect(x0, x1, z0, z1, k, mat, 1) {};
};

#endif
