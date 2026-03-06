#include "Scene.h"
#include <raylib.h>
#include <numbers>
#include <cmath>
#include <cstdint>
#include "Raytracer.h"

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
    //DrawPixel(10, 10, {255, 0, 0, 255});

    static float AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);
    static float VerticalFovDegrees = 60.f;
    static float HalfFovRads = (VerticalFovDegrees * 0.5f) * std::numbers::pi / 180.f;
    static float Fov = tanf(HalfFovRads);

    static Vector3f CameraPosition{0, 0, 0};

    static Raytracer Raytracer;
    
    for(int H=0; H < Height; ++H) 
    {
        for(int W=0; W < Width; ++W) 
        {
            float NDC_X = (static_cast<float>(W) + 0.5f) / static_cast<float>(Width);  //[0, 1]
            float NDC_Y = (static_cast<float>(H) + 0.5f) / static_cast<float>(Height); //[0, 1]

            float Plane_X = (2.f * NDC_X) - 1.f;  //[-1, 1]
            float Plane_Y = 1.f - (2.f * NDC_Y);  //[-1, 1]

            Plane_X = Plane_X * AspectRatio * Fov;
            Plane_Y = Plane_Y * Fov;

            Vector3f RayDirection = Vector3f{Plane_X, Plane_Y, CameraPosition.Z -1.f} - CameraPosition;
            RayDirection = RayDirection.Normalized();

            XRay PixelRay{CameraPosition, RayDirection};

            XColor PixelColor = Raytracer.Raytrace(PixelRay, *this);
            
            uint8_t R = static_cast<uint8_t>(PixelColor.R * 255.f);
            uint8_t G = static_cast<uint8_t>(PixelColor.G * 255.f);
            uint8_t B = static_cast<uint8_t>(PixelColor.B * 255.f);

            DrawPixel(W, H, {R, G, B, 255});
        }
    }

}

void Scene::Destroy() 
{ 

}

