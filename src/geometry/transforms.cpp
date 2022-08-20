#include "transforms.h"

bool Translation::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    Ray moved_r(r.origin()-offset, r.direction(), r.time());
    if(!ptr->hit(moved_r, t_min, t_max, rec))
        return false;
    rec.p += offset;
    return true;
}

bool Translation::bounding_box(double time0, double time1, AABB& output_box) const {
    if (!ptr->bounding_box(time0, time1, output_box))
        return false;
    output_box = AABB(output_box.minimum + offset, output_box.maximum + offset);
    return true;
}

RotateY::RotateY(const shared_ptr<Hittable>& p, double angle) :ptr(p) {
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    has_box = ptr->bounding_box(0, 1, bbox);

    Point3 min( infinity,  infinity,  infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i*bbox.maximum.x() + (1-i)*bbox.minimum.x();
                auto y = j*bbox.maximum.y() + (1-j)*bbox.minimum.y();
                auto z = k*bbox.maximum.z() + (1-k)*bbox.minimum.z();

                auto newx =  cos_theta*x + sin_theta*z;
                auto newz = -sin_theta*x + cos_theta*z;

                Vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = AABB(min, max);
}

bool RotateY::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta*r.origin()[0] - sin_theta*r.origin()[2];
    origin[2] = sin_theta*r.origin()[0] + cos_theta*r.origin()[2];

    direction[0] = cos_theta*r.direction()[0] - sin_theta*r.direction()[2];
    direction[2] = sin_theta*r.direction()[0] + cos_theta*r.direction()[2];

    Ray rotated_r(origin, direction, r.time());

    if (!ptr->hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] =  cos_theta*rec.p[0] + sin_theta*rec.p[2];
    p[2] = -sin_theta*rec.p[0] + cos_theta*rec.p[2];

    normal[0] =  cos_theta*rec.normal[0] + sin_theta*rec.normal[2];
    normal[2] = -sin_theta*rec.normal[0] + cos_theta*rec.normal[2];

    rec.update(rotated_r, normal, rec.mat_ptr, rec.t, rec.u, rec.v);

    return true;
}
