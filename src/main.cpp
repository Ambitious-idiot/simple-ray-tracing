# include <iostream>

int main() {
    const int img_width = 256;
    const int img_height = 256;
    std::cout << "P3\n" << img_width << ' '
        << img_height << "\n255\n";
    for (int j = img_height - 1; j >= 0; --j) {
        for (int i = 0; i < img_width; ++i) {
            auto r = double(i) / (img_width - 1);
            auto g = double(j) / (img_height - 1);
            auto b = 0.25;
            int ir = static_cast<int>(255.9999 * r);
            int ig = static_cast<int>(255.9999 * g);
            int ib = static_cast<int>(255.9999 * b);
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}