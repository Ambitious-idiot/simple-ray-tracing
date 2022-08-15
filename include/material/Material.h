#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "rtweekend.h"

struct Hit_record;

class Material {
    public:
        virtual bool scatter(
            const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered
        ) const = 0;
};

#endif