# include "rtweekend.h"

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
