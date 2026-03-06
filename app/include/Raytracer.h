#pragma once
#include "Vector3.h"
#include "Scene.h"
#include "XColor.h"

struct XRay 
{
    Vector3f Origin;
    Vector3f Direction;
};

struct RayHit {
    float Distance;
    const Sphere* Object;
    Vector3f Point;
    Vector3f Normal;
};

class Raytracer 
{
public:
    XColor Raytrace(const XRay& InRay, Scene& InScene, int InCurrentDepth);
};