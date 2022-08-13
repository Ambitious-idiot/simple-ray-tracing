# ifndef METAL_H
# define METAL_H

# include "material.h"

class Metal : public Material {
    public:
        Metal(const Color& a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        Color albedo;
};

# endif
