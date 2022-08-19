#ifndef BOX_H
#define BOX_H

#include "rectangle.h"
#include "hittable_list.h"

class Box : public Hittable  {
    Point3 box_min, box_max;
    HittableList sides;

    public:
        Box() {}
        Box(const Point3& p0, const Point3& p1, const shared_ptr<Material>& ptr);

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
            return sides.hit(r, t_min, t_max, rec);
        }

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override {
            output_box = AABB(box_min, box_max);
            return true;
        }
};

#endif
