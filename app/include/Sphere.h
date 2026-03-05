#pragma once
#include "Vector3.h"
#include "XColor.h"

struct XMaterial 
{
    XColor Albedo;
    float SpecularShiningFactor;
    float ReflectionFactor;
};

struct Sphere 
{
    Vector3f Center;
    float Radius;
    XMaterial Material;

    Sphere(const Vector3f& InCenter, float InRadius);
};