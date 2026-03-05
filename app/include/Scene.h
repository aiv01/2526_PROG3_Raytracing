#pragma once
#include <vector>
#include "Light.h"
#include "XColor.h"
#include "Sphere.h"


class Scene {
public:
    Scene(int w, int h);
    void Update(float delta_time);
    void Destroy();

public:    
    std::vector<Sphere> Spheres;
    Light Light;
    XColor BackgroundColor;

private:
    int Width;
    int Height;

};