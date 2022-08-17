# ifndef PERLIN_H
# define PERLIN_H

# include "Texture.h"

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

        virtual Color value(double u, double v, const Point3& p) const override {
            Point3 temp_p = p * scale;
            double ret = 0;
            double weight = 1;
            for (int i = 0; i < depth; i ++) {
                ret += weight * noise.noise(temp_p);
                weight *= 0.5;
                temp_p *= 2;
            }
            return Color(1, 1, 1) * fabs(ret);
        }
};

# endif
