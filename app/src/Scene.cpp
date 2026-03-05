#include "Scene.h"
#include <raylib.h>

Scene::Scene(int InWidth, int InHeight) 
{ 
    Width = InWidth;
    Height = InHeight;

    Sphere Sphere01{Vector3f{-1.5, 0, -5}, 1.f};
    Sphere01.Material.Albedo = {1, 0, 0};
    Sphere01.Material.SpecularShiningFactor = 40;
    Sphere01.Material.ReflectionFactor = 0.f;
 
    Sphere Sphere02{Vector3f{1.5, 0, -5}, 1.f};
    Sphere02.Material.Albedo = {0, 1, 0};
    Sphere02.Material.SpecularShiningFactor = 80;
    Sphere02.Material.ReflectionFactor = 0.8f;
 
    Sphere Sphere03{Vector3f{0, -1.5, -5}, 1.f};
    Sphere03.Material.Albedo = {0, 0, 1};
    Sphere03.Material.SpecularShiningFactor = 1000;
    Sphere03.Material.ReflectionFactor = 0.f;
 
    Spheres.push_back(Sphere01);
    Spheres.push_back(Sphere02);
    Spheres.push_back(Sphere03);
 
    Light.Direction = {0, -1, 0};
    Light.Color = {1, 0, 0};

    BackgroundColor = {0, 0, 0};
}

void Scene::Update(float InDeltaTime) 
{ 
    DrawPixel(10, 10, {255, 0, 0, 255});
    DrawPixel(11, 10, {255, 0, 0, 255});
    DrawPixel(12, 10, {255, 0, 0, 255});
}

void Scene::Destroy() 
{ 

}

