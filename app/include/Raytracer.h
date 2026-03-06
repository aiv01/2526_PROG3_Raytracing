#pragma once
#include "Vector3.h"
#include "Scene.h"
#include "XColor.h"

struct XRay 
{
    Vector3f Origin;
    Vector3f Direction;
};

class Raytracer 
{
public:
    XColor Raytrace(XRay InRay, Scene& InScene);
};