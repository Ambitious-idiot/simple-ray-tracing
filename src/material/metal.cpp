# include "metal.h"
# include "hittable.h"
#include "vec3.h"

bool Metal::scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const {
    Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz*random_unit_vector());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}
