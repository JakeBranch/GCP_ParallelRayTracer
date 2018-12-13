#include "RayTracer.h"
#include "Ray.h"
#include "Geometry.h"
#include "Sphere.h"

RayTracer::RayTracer()
{
    geometry = std::make_shared<Geometry>();
}

/**
* traceRay:
* 1) Loop through spheres and check if ray intersects and calculate color
* 2) If ray intersects create reflection and shadow rays and recursively call traceRay()
* 3) Color is returned via reference to variable
*/
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
                    glm::vec3 lightDirection = glm::normalize(glm::vec3(100, 100, 250) - response.intersectPoint);
                    glm::vec3 reflectDirection = glm::reflect(ray.getDirection(), surfaceNormal);

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
