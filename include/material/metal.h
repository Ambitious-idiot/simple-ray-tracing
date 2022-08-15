# ifndef METAL_H
# define METAL_H

# include "Material.h"

class Metal : public Material {
    public:
        Metal(const Color& a, double f) : albedo(a), fuzz(f < 1? f : 1) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        Color albedo;
        double fuzz;
};

# endif
