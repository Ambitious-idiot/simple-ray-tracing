#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "texture.h"
#include "vec3.h"

struct HitRecord;

class Material {
    public:
        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const = 0;

        virtual Color emit(double u, double v, const Point3& p) const {
            return Color(0, 0, 0);
        }
};

#endif
