#ifndef MIXED_TEXTURE_H
#define MIXED_TEXTURE_H

#include "Texture.h"
#include "vec3.h"
#include <vector>

class MixedTexture: public Texture {
    std::vector<shared_ptr<Texture>> textures;

    public:
        MixedTexture() {}

        void append(const shared_ptr<Texture> &texture) {
            textures.push_back(texture);
        }

        virtual Color value(double u, double v, const Point3& p) const override {
            Color ret(0, 0, 0);
            for (const shared_ptr<Texture>& texture: textures)
                ret += texture->value(u, v, p);
            return ret;
        }
};

#endif