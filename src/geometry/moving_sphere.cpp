# include "moving_sphere.h"

bool MovingSphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    Vec3 oc = r.origin() - center(r.time());
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
    rec.normal = (rec.p - center(r.time())) / radius;
    Vec3 outward_normal = (rec.p - center(r.time())) / radius;
    rec.set_face_normal(r, outward_normal);
    get_uv(outward_normal, rec.u, rec.v);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool MovingSphere::bounding_box(double _time0, double _time1, AABB& output_box) const {
    AABB box0(
        center(_time0) - Vec3(radius, radius, radius),
        center(_time0) + Vec3(radius, radius, radius));
    AABB box1(
        center(_time1) - Vec3(radius, radius, radius),
        center(_time1) + Vec3(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}

void MovingSphere::get_uv(const Point3 &p, double &u, double &v) {
    auto phi = atan2(-p.z(), p.x()) + pi;
    u = phi / (2*pi);
    auto theta = acos(-p.y());
    v = theta / pi;
}
