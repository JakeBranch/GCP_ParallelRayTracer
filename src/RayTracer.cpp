#include "RayTracer.h"
#include "Ray.h"
#include "Geometry.h"
#include "Sphere.h"

#include <iostream>

RayTracer::RayTracer()
{
    geometry = std::make_shared<Geometry>();

    bounceLimit = 1;
    bounceCount = 0;
}

void RayTracer::traceRay(Ray ray, glm::vec3 &color)
{
    float distance = 10000000;

    for(std::list<std::shared_ptr<Sphere>>::iterator it = spheres.begin();
        it != spheres.end(); it++)
    {
        // if(ray.getOrigin().x > 160)
        // {
        //     if(ray.getOrigin().y > 160)
        //     {
		// 		std::cout << "SDS" << std::endl;
        //     }
        // }

        IntersectResponse response = geometry->raySphereIntersection(ray, (*it));
        if(response.hit)
        {
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
                    glm::vec3 lightDirection = glm::normalize(glm::vec3(300, 300, -150) - response.intersectPoint);
                    // glm::vec3 lightDirection = glm::normalize(response.intersectPoint - glm::vec3(300,300,-150));

                    // glm::vec3 reflectDirection = (2 * (glm::dot(surfaceNormal, -lightDirection)) * surfaceNormal - lightDirection);
                    // glm::vec3 reflectDirection = lightDirection - 2 * glm::dot(lightDirection, surfaceNormal) * surfaceNormal;
                    // glm::vec3 reflectDirection = lightDirection * glm::dot(lightDirection, surfaceNormal) * surfaceNormal;
                    // glm::vec3 reflectDirection = (2 * glm::dot(surfaceNormal, lightDirection)) * surfaceNormal - lightDirection;
                    // glm::vec3 reflectDirection = (2 * (glm::dot(lightDirection, -surfaceNormal)) * surfaceNormal - lightDirection);

                    //--- Correct solutions..?
                    // glm::vec3 reflectDirection = glm::reflect(lightDirection, surfaceNormal);

                    // glm::vec3 reflectDirection = 2 * (glm::dot(lightDirection, surfaceNormal)) * surfaceNormal - lightDirection;
                    glm::vec3 reflectDirection = glm::reflect(ray.getDirection(), surfaceNormal);
                    // glm::vec3 reflectDirection = -lightDirection - (2.0f * glm::dot(surfaceNormal, -lightDirection)) * surfaceNormal;


                    Ray reflectRay;
                    reflectRay.setDirection(reflectDirection);
                    reflectRay.setOrigin(response.intersectPoint + surfaceNormal * 0.01f);
                    reflectRay.isPrimary = false;

                    bounceCount++;
                    traceRay(reflectRay, color);
                }
            }
        }
    }
}

void RayTracer::addSphere(std::shared_ptr<Sphere> sphere)
{
    spheres.push_back(sphere);
}

void RayTracer::reset()
{
    bounceCount = 0;
}