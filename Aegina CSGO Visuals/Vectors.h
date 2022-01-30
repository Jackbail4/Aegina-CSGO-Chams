#pragma once
#include <cmath>
#include <limits>

struct Vec2 {
    float x, y;
};
class Vec3
{
public:
    Vec3(void)
    {
        Invalidate();
    }
    Vec3(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
    }
    Vec3(const float* clr)
    {
        x = clr[0];
        y = clr[1];
        z = clr[2];
    }

    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
    {
        x = ix; y = iy; z = iz;
    }
    bool IsValid() const
    {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }
    void Invalidate()
    {
        x = y = z = std::numeric_limits<float>::infinity();
    }

    float& operator[](int i)
    {
        return ((float*)this)[i];
    }
    float operator[](int i) const
    {
        return ((float*)this)[i];
    }

    void Zero()
    {
        x = y = z = 0.0f;
    }

    bool operator==(const Vec3& src) const
    {
        return (src.x == x) && (src.y == y) && (src.z == z);
    }
    bool operator!=(const Vec3& src) const
    {
        return (src.x != x) || (src.y != y) || (src.z != z);
    }

    Vec3& operator+=(const Vec3& v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    Vec3& operator-=(const Vec3& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    Vec3& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }
    Vec3& operator*=(const Vec3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    Vec3& operator/=(const Vec3& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    Vec3& operator+=(float fl)
    {
        x += fl;
        y += fl;
        z += fl;
        return *this;
    }
    Vec3& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        z /= fl;
        return *this;
    }
    Vec3& operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        z -= fl;
        return *this;
    }

    void NormalizeInPlace()
    {
        *this = Normalized();
    }
    Vec3 Normalized() const
    {
        Vec3 res = *this;
        float l = res.Length();
        if (l != 0.0f) {
            res /= l;
        }
        else {
            res.x = res.y = res.z = 0.0f;
        }
        return res;
    }

    float DistTo(const Vec3& vOther) const
    {
        Vec3 delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.Length();
    }
    float DistToSqr(const Vec3& vOther) const
    {
        Vec3 delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.LengthSqr();
    }
    float Dot(const Vec3& vOther) const
    {
        return (x * vOther.x + y * vOther.y + z * vOther.z);
    }
    float Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }
    float LengthSqr(void) const
    {
        return (x * x + y * y + z * z);
    }
    float Length2D() const
    {
        return sqrt(x * x + y * y);
    }

    Vec3& operator=(const Vec3& vOther)
    {
        x = vOther.x; y = vOther.y; z = vOther.z;
        return *this;
    }

    Vec3 operator-(void) const
    {
        return Vec3(-x, -y, -z);
    }
    Vec3 operator+(const Vec3& v) const
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    Vec3 operator-(const Vec3& v) const
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }
    Vec3 operator*(float fl) const
    {
        return Vec3(x * fl, y * fl, z * fl);
    }
    Vec3 operator*(const Vec3& v) const
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }
    Vec3 operator/(float fl) const
    {
        return Vec3(x / fl, y / fl, z / fl);
    }
    Vec3 operator/(const Vec3& v) const
    {
        return Vec3(x / v.x, y / v.y, z / v.z);
    }
    void Normalize() {
        while (y < -179.f) { y += 359.f; }
        while (y > 179.f) { y -= 359.f; }
        if (x > 89.f) { x = 89.f; }
        if (x < -89.f) { x = -89.f; }
    }
    float x, y, z;
};
struct Vec4 {
    float x, y, z, w;
};
class matrix3x4_t {
    float* operator[ ](int index) {
        return matrix[index];
    }
    float matrix[3][4];
};
struct Matrix4x4 {
    union {
        struct {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;

        };
        float m[4][4];
    };
};