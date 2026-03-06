#include "Raytracer.h"
#include <cmath>

enum class ERayCastStrategy 
{
    RAYCAST_BEST,
    RAYCAST_FIRST
};

static bool RaySphereIntersection(const XRay& InRay, const Sphere& InSphere, RayHit& OutHit);
static bool RayCast(const XRay& InRay, Scene& InScene, ERayCastStrategy InStrategy, RayHit& HitOut);

XColor Raytracer::Raytrace(const XRay& InRay, Scene& InScene, int InCurrentDepth)
{
    if (InCurrentDepth > 3) return InScene.BackgroundColor;

    RayHit Hit;
    bool HasHit = RayCast(InRay, InScene, ERayCastStrategy::RAYCAST_BEST, Hit);
    //if (HasHit) return Hit.Object->Material.Albedo;
    if (!HasHit) return InScene.BackgroundColor;

    Vector3f InvertedLightDirection = InScene.Light.Direction * -1.f;

    static float Bias = 1e-4; //0.0004

    XRay ShadowRay;
    ShadowRay.Origin = Hit.Point + (Hit.Normal * Bias);
    ShadowRay.Direction = InvertedLightDirection;

    RayHit ShadowHit;
    bool HasShadowHit = RayCast(ShadowRay, InScene, ERayCastStrategy::RAYCAST_FIRST, ShadowHit);
    //if (HasShadowHit) return InScene.BackgroundColor;
    //return Hit.Object->Material.Albedo;

    XColor SphereColor = Hit.Object->Material.Albedo;

    // Ambient
    float AmbientFactor = 0.1f;
    XColor Ambient = SphereColor * AmbientFactor;

    // Diffuse
    float Lambert = fmaxf(0, InvertedLightDirection.Dot(Hit.Normal));
    XColor Diffuse = (SphereColor + InScene.Light.Color) * Lambert;

    // Specular
    Vector3f R = InScene.Light.Direction.Reflect(Hit.Normal);
    Vector3f E = (Hit.Point * -1.f).Normalized();
    float SpecularFactor = fmaxf(0, R.Dot(E));
    float SpecularInstensity = powf(SpecularFactor, Hit.Object->Material.SpecularShiningFactor);
    XColor Specular = InScene.Light.Color * SpecularInstensity;

    XColor Phong = Ambient + Diffuse + Specular;

    //Phong = Phong.Clamp();
    //return Phong;

    XColor FinalColor = Phong;

    if (Hit.Object->Material.ReflectionFactor > 0.f) 
    {
        XRay SecondRay;
        SecondRay.Origin = Hit.Point + (Hit.Normal * Bias);
        SecondRay.Direction = InRay.Direction.Reflect(Hit.Normal);

        XColor ReflectionColor = Raytrace(SecondRay, InScene, InCurrentDepth + 1);

        FinalColor = FinalColor + ReflectionColor * Hit.Object->Material.ReflectionFactor;
    }

    FinalColor = FinalColor.Clamp();
    return FinalColor;
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
    OutHit.Normal = (OutHit.Point - InSphere.Center).Normalized();
    return true;
}

bool RayCast(const XRay& InRay, Scene& InScene, ERayCastStrategy InStrategy, RayHit& OutHit) 
{
    RayHit BestHit;
    BestHit.Distance = std::numeric_limits<float>::max();

    bool HasBestHit = false;

    for(auto& Sphere: InScene.Spheres)
    {
        RayHit Hit;
        bool HasHit = RaySphereIntersection(InRay, Sphere, Hit);
        if (HasHit && Hit.Distance < BestHit.Distance) {
            BestHit = Hit;
            HasBestHit = true;

            if (InStrategy == ERayCastStrategy::RAYCAST_FIRST) break;
        }
    }

    if (HasBestHit) 
    {
        OutHit = BestHit;
    }
    return HasBestHit;
}
