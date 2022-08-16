# ifndef _MATERIAL_H
# define _MATERIAL_H

# include "texture.h"

struct HitRecord;

class Material {
    public:
        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const = 0;
};

# endif
