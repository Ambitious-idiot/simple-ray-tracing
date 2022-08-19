#include "color.h"
#include "geometry.h"
#include "camera.h"
#include "material.h"
#include <unistd.h>

// Scenes
HittableList random_scene() {
    HittableList world;

    auto checker = std::make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    world.append(make_shared<Sphere>(Point3(0,-1000,0), 1000, make_shared<Lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3(4, 0.2, 0)).len() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    auto center2 = center + Vec3(0, random_double(0, 0.2), 0);
                    world.append(make_shared<MovingSphere>(
                        center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.append(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.append(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.append(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.append(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.append(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

HittableList two_spheres() {
    HittableList objs;
    auto checker = make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    objs.append(make_shared<Sphere>(Point3(0, -10, 0), 10, make_shared<Lambertian>(checker)));
    objs.append(make_shared<Sphere>(Point3(0, 10, 0), 10, make_shared<LightSource>(checker)));
    return objs;
}

HittableList two_perlin_spheres() {
    HittableList objs;
    auto texture0 = make_shared<Turbulence>(4);
    auto texture1 = make_shared<MixedTexture>();
    texture1->append(make_shared<Marble>(5));
    texture1->append(make_shared<SolidColor>(Color(0.2, 0, 0)));
    objs.append(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(texture0)));
    objs.append(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<LightSource>(texture1)));
    return objs;
}

HittableList earth() {
    auto earth_texture = make_shared<ImageTexture>("imgs/earthmap.jpg");
    auto earth_surface = make_shared<Lambertian>(earth_texture);
    auto globe = make_shared<Sphere>(Point3(0,0,0), 2, earth_surface);
    auto texture = make_shared<SolidColor>(Color(4, 4, 4));
    auto light = make_shared<LightSource>(texture);
    auto rect = make_shared<XYRect>(0, 2, 0, 4, -3, light);
    auto world = HittableList();
    world.append(globe);
    world.append(rect);
    return world;
}

HittableList cornell_box() {
    HittableList objects;

    auto red   = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<LightSource>(Color(15, 15, 15));

    objects.append(make_shared<YZRect>(0, 555, 0, 555, 555, green));
    objects.append(make_shared<YZRect>(0, 555, 0, 555, 0, red));
    objects.append(make_shared<XZRect>(213, 343, 227, 332, 554, light));
    objects.append(make_shared<XZRect>(0, 555, 0, 555, 0, white));
    objects.append(make_shared<XZRect>(0, 555, 0, 555, 555, white));
    objects.append(make_shared<XYRect>(0, 555, 0, 555, 555, white));
    objects.append(make_shared<Box>(Point3(130, 0, 65), Point3(295, 165, 230), white));
    objects.append(make_shared<Box>(Point3(265, 0, 295), Point3(430, 330, 460), white));

    return objects;
}

HittableList color_box() {
    HittableList objs;
    objs.append(make_shared<XYRect>(-1, 1, -1, 1, 1, make_shared<Lambertian>(make_shared<SolidColor>(Color(0.2, 0, 0)))));
    objs.append(make_shared<XYRect>(-1, 1, -1, 1, -1, make_shared<Lambertian>(make_shared<SolidColor>(Color(0, 0.2, 0.2)))));
    objs.append(make_shared<YZRect>(-1, 1, -1, 1, 1, make_shared<Lambertian>(make_shared<SolidColor>(Color(0, 0.2, 0)))));
    objs.append(make_shared<YZRect>(-1, 1, -1, 1, -1, make_shared<Lambertian>(make_shared<SolidColor>(Color(0.2, 0, 0.2)))));
    objs.append(make_shared<XZRect>(-1, 1, -1, 1, 1, make_shared<Lambertian>(make_shared<SolidColor>(Color(0, 0, 0.2)))));
    objs.append(make_shared<XZRect>(-1, 1, -1, 1, -1, make_shared<Lambertian>(make_shared<SolidColor>(Color(0.2, 0.2, 0)))));
    objs.append(make_shared<YZRect>(-3, 3, -3, 3, -3, make_shared<Metal>(make_shared<SolidColor>(Color(1, 1, 1)), 0)));
    return objs;
}

// main
int main(int argc, char* argv[]) {
    // variable declarations
    HittableList (*world_constructors[])() = {
        random_scene, two_spheres, two_perlin_spheres,
        earth, cornell_box, color_box
    };
    HittableList (*world_constructor)() = random_scene;
    int img_width = 400;
    int spp = 100;
    int m_depth = 50;

    // read cmd args
    int ch;
    while ((ch = getopt(argc, argv, "c:w:p:d:")) != -1)
        switch (ch) {
            case 'c':
                world_constructor = world_constructors[atoi(optarg)];
                break;
            case 'w':
                img_width = atoi(optarg);
                break;
            case 'p':
                spp = atoi(optarg);
                break;
            case 'd':
                m_depth = atoi(optarg);
                break;
            default:
                abort();
        }

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    // const auto aspect_ratio = 1.0;
    const int image_width = img_width;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = spp;
    const int max_depth = m_depth;

    // World
    auto world = BVHNode(world_constructor(), 0.0, 1.0);
    const Color background(1, 1, 1);
    // const Color background(0, 0, 0);

    // Camera
    Point3 lookfrom(13,2,3);
    // Point3 lookfrom(278, 278, -800);
    Point3 lookat(0,0,0);
    // Point3 lookat(278, 278, 0);
    Vec3 vup(0,1,0);
    auto dist_to_focus = 10;
    auto aperture = 0.1;
    auto vfov = 20.0;
    // auto vfov = 40.0;

    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScan lines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
