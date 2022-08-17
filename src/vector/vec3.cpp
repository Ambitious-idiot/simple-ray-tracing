#include "rtweekend.h"

Vec3 refract(const Vec3& uv, const Vec3& n, double eta_i, double eta_t) {
    return refract(uv, n, eta_i/eta_t);
}
Vec3 refract(const Vec3& uv, const Vec3& n, double eta_divided) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp =  eta_divided * (uv + cos_theta*n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.len_square())) * n;
    return r_out_perp + r_out_parallel;
}

Vec3 Vec3::random() {
    return Vec3(random_double(), random_double(), random_double());
}
Vec3 Vec3::random(double min, double max) {
    return Vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

Vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Vec3::random(-1,1);
        if (p.len_square() >= 1) continue;
        return p;
    }
}

 Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.len_square() >= 1) continue;
        return p;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}
