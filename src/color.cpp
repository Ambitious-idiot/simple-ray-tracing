# include "color.h"

void write_color(std::ostream &out, const Color& px_color) {
    out << static_cast<int>(255.999 * px_color.x()) << ' '
        << static_cast<int>(255.999 * px_color.y()) << ' '
        << static_cast<int>(255.999 * px_color.z()) << '\n';
}
