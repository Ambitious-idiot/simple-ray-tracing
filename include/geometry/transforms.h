#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "hittable.h"

class Translation: public Hittable {
    shared_ptr<Hittable> ptr;
    Vec3 offset;

    public:
        Translation(const shared_ptr<Hittable>& p, const Vec3& displacement)
            : ptr(p), offset(displacement) {}

        virtual bool hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec
        ) const override;

        virtual bool bounding_box(
            double time0, double time1, AABB& output_box
        ) const override;
};


class RotateY: public Hittable {
    shared_ptr<Hittable> ptr;
    double sin_theta;
    double cos_theta;
    bool has_box;
    AABB bbox;

    public:
        RotateY(const shared_ptr<Hittable>& p, double angle);

        virtual bool hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec
        ) const override;

        virtual bool bounding_box(
            double time0, double time1, AABB& output_box
        ) const override {
            output_box = bbox;
            return has_box;
        }
};

#endif
