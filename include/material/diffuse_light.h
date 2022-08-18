#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "Material.h"

class DiffuseLight: public Material {
    shared_ptr<Texture> texture;

    public:
        DiffuseLight(const shared_ptr<Texture>& t): texture(t) {}
        DiffuseLight(Color c): texture(make_shared<SolidColor>(c)) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override { return false; }

        virtual Color emit(double u, double v, const Point3& p) const override {
            return texture->value(u, v, p);
        }
};

#endif