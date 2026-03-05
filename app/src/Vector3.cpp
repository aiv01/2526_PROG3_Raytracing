#include "Vector3.h"
#include <cmath>

 Vector3f::Vector3f() 
    : X(0), Y(0), Z(0) { }


Vector3f::Vector3f(float InX, float InY, float InZ) 
    : X(InX), Y(InY), Z(InZ) { }

Vector3f Vector3f::operator-(const Vector3f& InOther) const
{
    return Vector3f{X - InOther.X, Y - InOther.Y, Z - InOther.Z};
}

Vector3f Vector3f::operator+(const Vector3f& InOther) const
{
    return Vector3f{X + InOther.X, Y + InOther.Y, Z + InOther.Z};
}

Vector3f Vector3f::operator/(const float InScalar) const
{
    return Vector3f{X / InScalar, Y / InScalar, Z / InScalar};
}

Vector3f Vector3f::operator*(const float InScalar) const
{
    return Vector3f{X * InScalar, Y * InScalar, Z * InScalar};
}


Vector3f Vector3f::Normalized() const 
{
    return *this / Magnitude();
}

float Vector3f::Magnitude() const 
{
    return sqrtf(MagnitudeSquared());
}

float Vector3f::MagnitudeSquared() const 
{
    return Dot(*this);
}

float Vector3f::Dot(const Vector3f& InOther) const
{
    return X * InOther.X + Y * InOther.Y + Z * InOther.Z;
}

Vector3f Vector3f::Reflect(const Vector3f& InNorm) const 
{
    //R = I – 2 * dot(I,N) * N
    return *this - InNorm * (2.f * this->Dot(InNorm));
}