# ifndef CHECKER_TEXTURE_H
# define CHECKER_TEXTURE_H

# include "solid_color.h"

class CheckerTexture: public Texture {
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;

    public:
        CheckerTexture() {}
        CheckerTexture(const shared_ptr<Texture>& t1, const shared_ptr<Texture>& t2)
            : even(t1), odd(t2) {}
        CheckerTexture(Color c1, Color c2)
            : even(make_shared<SolidColor>(c1)), odd(make_shared<SolidColor>(c2)) {}

        virtual Color value(double u, double v, const Point3& p) const override {
            return sin(10*p[0])*sin(10*p[1])*sin(10*p[2]) < 0 ?
            odd->value(u, v, p) : even->value(u, v, p);
        }
};

# endif