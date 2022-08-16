# ifndef LAMBERTIAN_H
# define LAMBERTIAN_H

# include "Material.h"

class Lambertian : public Material {
    public:
        Lambertian(const shared_ptr<Texture>& a): albedo(a) {}
        Lambertian(const Color& a) : albedo(make_shared<SolidColor>(a)) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        shared_ptr<Texture> albedo;
};

# endif
