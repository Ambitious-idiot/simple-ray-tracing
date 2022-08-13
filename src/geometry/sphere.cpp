# include "sphere.h"

bool Sphere::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const {
    Vec3 oc = r.origin() - center;
    auto a = r.direction().len_square();
    auto half_b = dot(oc, r.direction());
    auto c = oc.len_square() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrt_d = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrt_d) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrt_d) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}