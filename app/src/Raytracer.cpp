#include "Raytracer.h"
#include <cmath>

static bool RaySphereIntersection(const XRay& InRay, const Sphere& InSphere, RayHit& OutHit);
static bool RayCast(const XRay& InRay, Scene& InScene, RayHit& HitOut);

XColor Raytracer::Raytrace(const XRay& InRay, Scene& InScene)
{
    RayHit Hit;
    bool HasHit = RayCast(InRay, InScene, Hit);
    if (HasHit) {
        return Hit.Object->Material.Albedo;
    }
    return InScene.BackgroundColor;
}

bool RaySphereIntersection(const XRay& InRay, const Sphere& InSphere, RayHit& OutHit) 
{
    Vector3f L = InSphere.Center - InRay.Origin;
    float Tca = L.Dot(InRay.Direction);

    float MagnL2 = L.MagnitudeSquared();
    float D2 = MagnL2 - Tca * Tca;
    float Radius2 = InSphere.Radius * InSphere.Radius;
    if (D2 > Radius2) return false;

    float Thc = sqrtf(Radius2 - D2);

    float T0 = Tca - Thc;
    float T1 = Tca + Thc;

    if (T1 < T0) 
    {
        float Temp = T0;
        T0 = T1;
        T1 = Temp;
    }

    if (T0 < 0) 
    {
        T0 = T1;
        if (T0 < 0) return false;
    }

    OutHit.Distance = T0;
    OutHit.Object = &InSphere;
    OutHit.Point = InRay.Origin + InRay.Direction * T0;
    return true;
}

bool RayCast(const XRay& InRay, Scene& InScene, RayHit& HitOut) 
{
    for(auto& Sphere: InScene.Spheres)
    {
        RayHit Hit;
        bool HasHit = RaySphereIntersection(InRay, Sphere, Hit);
        if (HasHit) {
            HitOut = Hit;
            return true;
        }
    }

    return false;
}
