# ifndef PERLIN_H
# define PERLIN_H

# include "Texture.h"

class Perlin {
    static const int point_count = 256;
    double* random_floats;
    int* perm_x, * perm_y, * perm_z;

    public:
        Perlin();
        ~Perlin();

        double noise(const Point3& p) const;

    private:
        static int* perlin_generate_perm();
        static void permute(int* p, int n);
};


class NoiseTexture: public Texture {
    Perlin noise;

    public:
        NoiseTexture() {}

        virtual Color value(double u, double v, const Point3& p) const override {
            return Color(1, 1, 1) * noise.noise(p);
        }
};

# endif
