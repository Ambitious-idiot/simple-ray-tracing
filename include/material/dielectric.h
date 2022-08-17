#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

class Dielectric : public Material {
    public:
        Dielectric(double eta) : eta(eta) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        double eta;

    private:
        static double reflectance(double cosine, double ref_idx);
};

#endif
