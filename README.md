# Ray Tracing in One Weekend
This repo is a simple implementation of ray tracing based on [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) and [_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html). In this implementation some issues in the original code are fixed and some structures of codes are changed. Also some new features and examples are added. However there is still a bug when rendering Cornell box that the front box is blocked by the other.
## Output a PPM image
Write the rgb triplets to the file with the redirection '>'
## Implement point, color and ray as Vec3
First implement class Vec3 and directly typedef point and color as Vec3, then implement ray with two Vec3.
## Add hittable
Implement abstract base class Hittable with virtual function hit, then implement sphere and hittable list.
When implementing box, find bug in the book that it doesn't compare which hit happens first, which is the real hit, so add checking whether t of new hit is greater than that rec stores
## Add camera
Capsule the aspect ratio, focal length... in a class
## Add antialias
Simple antialias by sampling.
## Implement diffuse
with output direction randomly chosen and recursively compute the reflection with an upper bound of reflection times.
## Gamma correction
correct rgb computing from linear to sqrt
## Materials
### Abstract class
virtual function scatter
### Lambertian
Pure diffusion
### Metal
Pure reflection
### Something about linking
Material has a Hit_record member while Hittable_record has a Material member, must declare the class in x.h and include both x.h and y.h in .cpp
### metal fuzz
Pure reflection also has a fuzz, add fuzzy * random_vector().
### Dielectrics
has both reflection/scatter and refraction
With Snell's law, we have $R^\prime_\perp=\frac{\eta}{\eta^\prime}(R+n\cos\theta)=\frac{\eta}{\eta^\prime}(R-R\cdot nn)$
For full reflection's sake, must switch whether refract.
Schlick's approximation
## Camera
fov
set the lookfrom and the view square
## Defocus blur
# The Next Week
## Motion blur
store existing time of rays and keep the camera in track of time. add moving objects
## Bounding volume hierarchies
accelerate ray-obj intersection computing.
Split the space into non-intersection parts to build the tree.
### AABBs
every hittables' AABBs can be solved and the hittable list's is the union of the members'.
### BVH Tree
build two-branch tree(kd tree) of hittables and the leaves are hittables except BVHNode while the others are all the latter. Hit-examination is actually a pre-order traversal. The building scheme:
1. randomly choose an axis
2. sort the primitives (using std::sort)
3. put half in each subtree
Compare the program with and without BVH, the same image is rendered in 10m6s without BVH while in 59s with BVH.
## Texture
build class Texture, add uv-solving function in Sphere::hit, insert texture to material::scatter.
### Perlin Noise
looks like blurred white noise. It takes a 3D point as input and the result is repeatable. Nearby points return similar numbers.
To smooth the output, apply tri-lerp to the output.
To address the Mach bands, use Hermitian smoothing.
To get higher-frequency texture, add arg scale.
To make the texture less blocky looking, use random unit vectors rather than doubles. When calculating noise, use dot(rand_vec, weight).
Turbulence: sum of Perlin noise with different frequencies.
Marble: add regular phase change to turbulence.
### Image texture
convert image to u-v so that the size of texture map doesn't suffer from the resolution. The conversion is totally a resizing transform.
### Mixed texture
NOT IN THE BOOKS try to bind several textures together to form a new texture.
## Rectangles and Light
### Light source
add emit in class Material, refactory ray_color to return emitted light and background light.
### Rectangles
axis-aligned. UV is linear resizing.
### Cornell box
### Box
## Transforms
### Translation
Translate the ray to reach the object and calculate the hit point.
### Rotation
Take y as the pivot,
$x^\prime=\cos\theta\cdot x+\sin\theta\cdot z$
$z^\prime=???\sin\theta\cdot x+\cos\theta\cdot z$
