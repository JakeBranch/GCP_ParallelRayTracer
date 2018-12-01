#include "Geometry.h"
#include "sphere.h"
#include "Ray.h"

Geometry::Geometry()
{

}

glm::vec3 Geometry::getClosestPoint(Ray ray, std::shared_ptr<Sphere> sphere)
{
    glm::vec3 a = ray.getOrigin() - glm::vec3(0,0,0);  
    glm::vec3 p = sphere->getPosition() - glm::vec3(0,0,0);

    glm::vec3 rayDirection = glm::normalize(ray.getDirection());

    return a + ((p - a) * rayDirection) * rayDirection;
}

glm::vec3 Geometry::getClosestIntersectionPoint(Ray ray, std::shared_ptr<Sphere> sphere, float distance)
{
    glm::vec3 rayDirection = glm::normalize(ray.getDirection());
    float x = glm::sqrt((sphere->getRadius() * sphere->getRadius()) - (distance * distance));
    glm::vec3 a = ray.getOrigin() - glm::vec3(0,0,0);
    glm::vec3 p = sphere->getPosition() - glm::vec3(0,0,0);

    return a + (glm::dot((p - a), rayDirection) - x) * rayDirection;
}

IntersectResponse Geometry::raySphereIntersection(Ray ray, std::shared_ptr<Sphere> sphere)
{
    IntersectResponse response;

    glm::vec3 x = getClosestPoint(ray, sphere);
    glm::vec3 p = sphere->getPosition() - glm::vec3(0,0,0);

    float distance = glm::length(p - x);
    response.distance = distance;

    if(distance > sphere->getRadius())
    {
        response.hit = false;
        return response;
    }
    else
    {
        response.hit = true;
    }

    response.intersectPoint = getClosestIntersectionPoint(ray, sphere, distance);
   
    return response;
}