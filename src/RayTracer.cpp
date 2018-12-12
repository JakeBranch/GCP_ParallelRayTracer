#include "RayTracer.h"
#include "Ray.h"
#include "Geometry.h"
#include "Sphere.h"

#include <iostream>

RayTracer::RayTracer()
{
    geometry = std::make_shared<Geometry>();
}

void RayTracer::traceRay(Ray ray, glm::vec3 &color)
{
    float distance = 10000000;

    for(std::list<std::shared_ptr<Sphere>>::iterator it = spheres.begin();
        it != spheres.end(); it++)
    {
        IntersectResponse response = geometry->raySphereIntersection(ray, (*it));
        if(response.hit)
        {
            if(ray.isShadow)
            {
                color =  glm::vec3(0,0,0);
                return;
            }
            if(response.distance < distance)
            {
                distance = response.distance;

                if(ray.isPrimary)
                    color = (*it)->shade(ray, response.intersectPoint);
                else
                    color += ((*it)->shade(ray, response.intersectPoint) * 1.0f);

                if(ray.isPrimary)
                {
                    glm::vec3 surfaceNormal = (response.intersectPoint - (*it)->getPosition()) / (*it)->getRadius();

                    glm::vec3 lightDirection = glm::normalize(glm::vec3(0, 100, 125) - response.intersectPoint);

                    // glm::vec3 reflectDirection = 2 * (glm::dot(lightDirection, surfaceNormal)) * surfaceNormal - lightDirection;
                    glm::vec3 reflectDirection = glm::reflect(ray.getDirection(), surfaceNormal);
                    // glm::vec3 reflectDirection = -lightDirection - (2.0f * glm::dot(surfaceNormal, -lightDirection)) * surfaceNormal;

                    Ray reflectRay;
                    reflectRay.setDirection(reflectDirection);
                    reflectRay.setOrigin(response.intersectPoint + surfaceNormal * 0.01f);
                    reflectRay.isPrimary = false;

                    traceRay(reflectRay, color);

                    Ray shadowRay;
                    shadowRay.setDirection(lightDirection);
                    shadowRay.setOrigin(response.intersectPoint + surfaceNormal * 0.01f);
                    shadowRay.isPrimary = false;
                    shadowRay.isShadow = true;
                    traceRay(shadowRay, color);
                }
            }
        }
    }
}

void RayTracer::addSphere(std::shared_ptr<Sphere> sphere)
{
    spheres.push_back(sphere);
}
