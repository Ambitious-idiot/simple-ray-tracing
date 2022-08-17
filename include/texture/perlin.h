# ifndef PERLIN_H
# define PERLIN_H

# include "Texture.h"
#include "vec3.h"

class Perlin {
    static const int point_count = 256;
    Vec3* random_vecs;
    int* perm_x, * perm_y, * perm_z;

    public:
        Perlin();
        ~Perlin();

        double noise(const Point3& p) const;

    private:
        static int* perlin_generate_perm();
};


class NoiseTexture: public Texture {
    Perlin noise;
    double scale;

    public:
        NoiseTexture() {}
        NoiseTexture(double s): scale(s) {}

        virtual Color value(double u, double v, const Point3& p) const override {
            return Color(0.5, 0.5, 0.5) * (1 + noise.noise(scale*p));
        }
};

# endif
