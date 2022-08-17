#include "hittable_list.h"

bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool HittableList::bounding_box(double time0, double time1, AABB &output_box) const {
    if (objects.empty()) return false;
    AABB box;
    bool first = true;
    for(const auto &obj: objects) {
        if(!obj->bounding_box(time0, time1, box)) return false;
        if (first) {
            first = false;
            output_box = box;
        }
        else output_box = surrounding_box(output_box, box);
    }
    return true;
}
