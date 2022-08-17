#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "Texture.h"

class ImageTexture : public Texture {
    unsigned char* data;
    int width, height;
    int bytes_per_scanline;

    public:
        const static int bytes_per_pixel = 3;

        ImageTexture()
          : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

        ImageTexture(const char* filename);

        ~ImageTexture() {
            delete data;
        }

        virtual Color value(double u, double v, const Vec3& p) const override;
};

#endif
