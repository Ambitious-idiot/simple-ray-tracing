#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
    Point3 center;
    double radius;
    shared_ptr<Material> mat_ptr;

    public:
        Sphere() {}
        Sphere(Point3 cen, double r, const shared_ptr<Material> &m)
         : center(cen), radius(r), mat_ptr(m) {}

        virtual bool hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

        static void get_uv(const Point3& p, double& u, double& v);
};

#endif
