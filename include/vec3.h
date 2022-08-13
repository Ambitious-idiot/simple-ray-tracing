# ifndef VEC3_H
# define VEC3_H

# include <cmath>
# include <iostream>

using std::sqrt;

class Vec3 {
    double value[3];

    public:
        Vec3(): value{0, 0, 0} {}
        Vec3(double x, double y, double z): value{x, y, z} {}

        double x() const {return value[0];}
        double y() const {return value[1];}
        double z() const {return value[2];}

        Vec3 operator-() const {return Vec3(-value[0], value[1], value[2]);}
        double operator[](int i) const {return value[i];}
        double& operator[](int i) {return value[i];}

        Vec3& operator+=(const Vec3& v) {
           value[0] += v[0];
           value[1] += v[1];
           value[2] += v[2];
           return *this;
        }
        Vec3& operator*=(const double v) {
            value[0] *= v;
            value[1] *= v;
            value[2] *= v;
            return *this;
        }
        Vec3& operator/=(const double t) {return *this *= 1/t;}

        double len() const {return sqrt(len_square());}
        double len_square() const {
            return value[0]*value[0]+value[1]*value[1]+value[2]*value[2];
        }

        static Vec3 random();
        static Vec3 random(double min, double max);
    };

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v[0], t*v[1], t*v[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return u[0] * v[0]
         + u[1] * v[1]
         + u[2] * v[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.len();
}

Vec3 random_in_unit_sphere();
Vec3 random_unit_vector();

using Point3 = Vec3;
using Color = Vec3;

# endif
