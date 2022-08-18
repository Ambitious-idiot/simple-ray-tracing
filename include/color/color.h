#ifndef COLOR_H
#define COLOR_H

#include "hittable.h"

void write_color(std::ostream &out, const Color& px_color, int samples_per_pixel);
Color ray_color(const Ray& r, const Color& background, const Hittable& world, int depth);

#endif
