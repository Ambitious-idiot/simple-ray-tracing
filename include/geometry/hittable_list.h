#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
    public:
        HittableList() {}

        void clear() { objects.clear(); }
        void append(const shared_ptr<Hittable> &object) { objects.push_back(object); }

        virtual bool hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

    public:
        std::vector<shared_ptr<Hittable>> objects;
};

#endif
