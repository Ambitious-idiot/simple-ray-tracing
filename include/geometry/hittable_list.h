#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "rtweekend.h"

#include <memory>
#include <vector>

class Hittable_list : public Hittable {
    public:
        Hittable_list() {}

        void clear() { objects.clear(); }
        void append(const shared_ptr<Hittable> &object) { objects.push_back(object); }

        virtual bool hit(
            const Ray& r, double t_min, double t_max, Hit_record& rec) const override;

    public:
        std::vector<shared_ptr<Hittable>> objects;
};

#endif
