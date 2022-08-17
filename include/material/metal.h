# ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material {
    public:
        Metal(const shared_ptr<Texture>& a, double f): albedo(a), fuzz(f < 1 ? f : 1) {}
        Metal(const Color& a, double f) : albedo(make_shared<SolidColor>(a)), fuzz(f < 1? f : 1) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        shared_ptr<Texture> albedo;
        double fuzz;
};

#endif
