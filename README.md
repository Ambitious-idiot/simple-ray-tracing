# Ray Tracing in One Weekend
## Output a PPM image
Write the rgb triplets to the file with the redirection '>'
## Implement point, color and ray as Vec3
First implement class Vec3 and directly typedef point and color as Vec3, then implement ray with two Vec3.
## Add hittable
Implement abstract base class Hittable with virtual function hit, then implement sphere and hittable list.
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
## Perlin Noise
looks like blurred white noise. It takes a 3D point as input and the result is repeatable. Nearby points return similar numbers.
To smooth the output, apply tri-lerp to the output.
To address the Mach bands, use Hermitian smoothing.
To get higher-frequency texture, add arg scale.
To make the texture less blocky looking, use random unit vectors rather than doubles. When calculating noise, use dot(rand_vec, weight).
Turbulence: sum of Perlin noise with different frequencies.