# include "lambertian.h"
# include "hittable.h"

bool Lambertian::scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const {
    auto scatter_direction = rec.normal + random_unit_vector();
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;
    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}