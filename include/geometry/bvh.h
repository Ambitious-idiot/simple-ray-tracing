#ifndef BVH_H
#define BVH_H

#include "hittable_list.h"
#include <vector>

class BVHNode: public Hittable {
    public:
        shared_ptr<Hittable> left, right;
        AABB box;

    public:
        BVHNode() {}
        BVHNode(
            const std::vector<shared_ptr<Hittable>> &objs,
            size_t start, size_t end, double time0, double time1);
        BVHNode(const HittableList& objs, double time0, double time1)
            : BVHNode(objs.objects, 0, objs.objects.size(), time0, time1)
        {}

        virtual bool hit(
            const Ray &r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

};

inline bool box_compare(const shared_ptr<Hittable> &a, const shared_ptr<Hittable> &b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.minimum[axis] < box_b.minimum[axis];
}


inline bool box_x_compare (const shared_ptr<Hittable> &a, const shared_ptr<Hittable> &b) {
    return box_compare(a, b, 0);
}

inline bool box_y_compare (const shared_ptr<Hittable> &a, const shared_ptr<Hittable> &b) {
    return box_compare(a, b, 1);
}

inline bool box_z_compare (const shared_ptr<Hittable> &a, const shared_ptr<Hittable> &b) {
    return box_compare(a, b, 2);
}

#endif
