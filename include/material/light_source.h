#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include "Material.h"

class LightSource: public Material {
    shared_ptr<Texture> texture;

    public:
        LightSource(const shared_ptr<Texture>& t): texture(t) {}
        LightSource(Color c): texture(make_shared<SolidColor>(c)) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override { return false; }

        virtual Color emit(double u, double v, const Point3& p) const override {
            return texture->value(u, v, p);
        }
};

#endif
