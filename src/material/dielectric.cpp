# include "dielectric.h"
# include "hittable.h"
# include "vec3.h"

bool Dielectric::scatter(const Ray  & r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    attenuation = Color(1.0, 1.0, 1.0);
    Vec3 unit_direction = r_in.direction();
    double refraction_ratio = rec.front_face ? (1.0/eta) : eta;
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    bool cannot_refract = refraction_ratio * refraction_ratio * (1.0 - cos_theta*cos_theta) > 1.0;
    Vec3 direction;
    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    scattered = Ray(rec.p, direction, r_in.time());
    return true;
}

double Dielectric::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}
