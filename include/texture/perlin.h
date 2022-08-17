#ifndef PERLIN_H
#define PERLIN_H

#include "Texture.h"

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
    protected:
        Perlin noise;
        double scale;

    public:
        NoiseTexture() {}
        NoiseTexture(double s): scale(s) {}

        virtual Color value(double u, double v, const Point3& p) const override {
            return Color(0.5, 0.5, 0.5) * (1 + noise.noise(scale*p));
        }
};

class Turbulence: public NoiseTexture {
    int depth;

    public:
        Turbulence() {}
        Turbulence(double s, int d=7): NoiseTexture(s), depth(d) {}

        virtual Color value(double u, double v, const Point3& p) const override;
};

class Marble: public Turbulence {
    int turb_weight;

    public:
        Marble() {}
        Marble(double s, int t_w=5, int d=7): Turbulence(s, d), turb_weight(t_w) {}

        virtual Color value(double u, double v, const Point3& p) const override {
            return Color(0.5, 0.5, 0.5) * (1+sin(scale*p.z()))
                + turb_weight * Turbulence::value(u, v, p);
        }
};

#endif
