#include "metal.h"
#include "hittable.h"
#include "vec3.h"

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz*random_unit_vector(), r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return (dot(scattered.direction(), rec.normal) > 0);
}
