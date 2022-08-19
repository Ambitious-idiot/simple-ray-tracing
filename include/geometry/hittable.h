#ifndef HITTABLE_H
#define HITTABLE_H

#include "aabb.h"
#include "Material.h"

class HitRecord {
    public:
        Point3 p;
        Vec3 normal;
        shared_ptr<Material> mat_ptr;
        double t;
        double u, v;
        bool front_face;

    public:
        HitRecord(): t(infinity) {}

        void update(const Ray& r, Vec3 _normal, const shared_ptr<Material>& _mat_ptr, double _t, double _u, double _v) {
            if (t < _t)
                return;
            t = _t;
            p = r.at(_t);
            normal = _normal;
            set_face_normal(r);
            u = _u;
            v = _v;
            mat_ptr = _mat_ptr;
        }

        void set_face_normal(const Ray& r) {
            front_face = dot(r.direction(), normal) < 0;
            normal = front_face ? normal :-normal;
        }
};

class Hittable {
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
        virtual bool bounding_box(double time0, double time1, AABB& output_box) const = 0;
};

#endif
