# ifndef LAMBERTIAN_H
# define LAMBERTIAN_H

# include "Material.h"

class Lambertian : public Material {
    public:
        Lambertian(const Color& a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        Color albedo;
};

# endif
