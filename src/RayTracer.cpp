#include "RayTracer.h"
#include "Ray.h"
#include "Geometry.h"
#include "Sphere.h"

RayTracer::RayTracer()
{
    geometry = std::make_shared<Geometry>();
}

glm::vec3 RayTracer::traceRay(Ray ray)
{
    glm::vec3 color = glm::vec3(0,0,0);
    float distance = 10000000;

    for(std::list<std::shared_ptr<Sphere>>::iterator it = spheres.begin();
        it != spheres.end(); it++)
    {
        IntersectResponse response = geometry->raySphereIntersection(ray, (*it));
        if(response.hit)
        {
            if(response.distance < distance)
            {
                color = (*it)->shade(ray, response.intersectPoint);
                distance = response.distance;
            }
        }
    }

    return color;
}

void RayTracer::addSphere(std::shared_ptr<Sphere> sphere)
{
    spheres.push_back(sphere);
}