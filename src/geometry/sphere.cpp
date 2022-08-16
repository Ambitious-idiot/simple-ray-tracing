# include "sphere.h"

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

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    get_uv(outward_normal, rec.u, rec.v);
    rec.mat_ptr = mat_ptr;

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
