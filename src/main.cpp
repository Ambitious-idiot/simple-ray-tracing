# include "color.h"
# include "geometry.h"
# include "camera.h"
# include "material.h"
#include <cstdlib>
# include <unistd.h>

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
    objs.append(make_shared<Sphere>(Point3(0, 10, 0), 10, make_shared<Lambertian>(checker)));
    return objs;
}


int main(int argc, char* argv[]) {
    // variable declarations
    HittableList (*world_constructors[2])() = {random_scene, two_spheres};
    HittableList (*world_constructor)() = random_scene;
    double t_start = 0;
    double t_end = 0;
    int image_width = 1024;
    int image_height = 576;
    int samples_per_pixel = 200;
    int max_depth = 50;

    // read cmd args
    int ch;
    while ((ch = getopt(argc, argv, "c:s:e:w:h:p:d:")) != -1)
        switch (ch) {
            case 'c':
                world_constructor = world_constructors[atoi(optarg)];
                break;
            case 's':
                t_start = atof(optarg);
                break;
            case 'e':
                t_end = atof(optarg);
                break;
            case 'w':
                image_width = atoi(optarg);
                break;
            case 'h':
                image_height = atoi(optarg);
                break;
            case 'p':
                samples_per_pixel = atoi(optarg);
                break;
            case 'd':
                max_depth = atoi(optarg);
                break;
            default:
                abort();
        }

    const auto aspect_ratio = image_width/image_height;

    // World
    auto world = BVHNode(world_constructor(), t_start, t_end);

    // Camera
    Point3 lookfrom(13,2,3);
    Point3 lookat(0,0,0);
    Vec3 vup(0,1,0);
    auto dist_to_focus = 10;
    auto aperture = 0.1;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

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
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
