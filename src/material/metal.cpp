# include "metal.h"
# include "hittable.h"

bool Metal::scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const {
    Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}
