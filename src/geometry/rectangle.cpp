#include "rectangle.h"

bool AARect::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    auto t = (k - r.origin()[axis]) / r.direction()[axis];
    if (t < t_min || t > t_max)
        return false;
    double uv[2];
    for (int i = 0, idx = 0, cnt = 0; i < 3; i ++) {
        if (i == axis) continue;
        auto _a = r.origin()[i] + t*r.direction()[i];
        if (_a < a[idx++]) return false;
        if (_a > a[idx++]) return false;
        uv[cnt++] = (_a-a[idx-2])/(a[idx-1]-a[idx-2]);
    }
    rec.u = uv[0];
    rec.v = uv[1];
    rec.t = t;
    auto outward_normal = !axis ? Vec3(1, 0, 0) : axis == 1 ? Vec3(0, 1, 0) : Vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.p = r.at(t);
    return true;
}

bool AARect::bounding_box(double time0, double time1, AABB& output_box) const {
    Point3 p0, p1;
    for(int i = 0, idx = 0; i < 3; i ++) {
        if (i == axis) {
            p0[i] = k - 0.0001;
            p1[i] = k + 0.0001;
            continue;
        }
        p0[i] = a[idx ++];
        p1[i] = a[idx ++];
    }
    output_box = AABB(p0, p1);
    return true;
}
