#include "sphere.h"

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
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

    Vec3 normal = (r.at(root) - center) / radius;
    double u, v;
    get_uv(normal, u, v);
    rec.update(r, normal, mat_ptr, root, u, v);
    return true;
}

bool Sphere::bounding_box(double time0, double time1, AABB &output_box) const {
    output_box = AABB(center-Vec3(radius, radius, radius), center+Vec3(radius, radius, radius));
    return true;
}

void Sphere::get_uv(const Point3 &p, double &u, double &v) {
    auto phi = atan2(-p.z(), p.x()) + pi;
    u = phi / (2*pi);
    auto theta = acos(-p.y());
    v = theta / pi;
}
