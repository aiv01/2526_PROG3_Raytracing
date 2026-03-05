#pragma once

struct Vector3f {
    float X;
    float Y;
    float Z;

    Vector3f();

    Vector3f(float InX, float InY, float InZ);

    Vector3f operator-(const Vector3f& InOther) const;

    Vector3f operator+(const Vector3f& InOther) const;

    Vector3f operator/(const float InScalar) const;

    Vector3f operator*(const float InScalar) const;

    Vector3f Normalized() const;

    float Magnitude() const;

    float MagnitudeSquared() const;

    float Dot(const Vector3f& InOther) const;

    Vector3f Reflect(const Vector3f& InNorm) const;
};