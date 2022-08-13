# Ray Tracing in One Weekend Notes
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