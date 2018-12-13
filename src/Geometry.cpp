#include "Geometry.h"
#include "sphere.h"
#include "Ray.h"

Geometry::Geometry()
{

}

/*
* getIntersectPoint:
* 1) Check if ray origin is inside sphere
* 2) Calculate shortest distance from sphere origin to the ray 
* 3) Calculate intersect response
* 4) Calculate distance to intersect
*/
IntersectResponse Geometry::getIntersectPoint(Ray ray, std::shared_ptr<Sphere> sphere)
{
    IntersectResponse rtn;

    float distToCenter = glm::length(ray.getOrigin() - sphere->getPosition());
    if(distToCenter <= sphere->getRadius())
    {
        rtn.hit = false;
        return rtn;
    }

    glm::vec3 a = ray.getOrigin() - glm::vec3(0,0,0);  
    glm::vec3 p = sphere->getPosition() - glm::vec3(0,0,0);

    glm::vec3 rayDirection = glm::normalize(ray.getDirection());

    glm::vec3 closestPointOnLine = a + (glm::dot((p - a) , rayDirection) * rayDirection);

    float pointToLine = glm::length(p - closestPointOnLine);

    if(pointToLine > sphere->getRadius())
    {
        rtn.hit = false;
        return rtn;
    }

    rtn.hit = true;

    // rtn.distance = pointToLine;
    float distanceToIntersect = glm::sqrt((sphere->getRadius() * sphere->getRadius()) - (pointToLine * pointToLine));

    //distance to intersect
    float tempDist = (glm::dot((p - a), rayDirection) - distanceToIntersect);

    if(tempDist < 0)
    {
        rtn.hit = false;
        return rtn;
    }

    rtn.intersectPoint = a + tempDist * rayDirection;

    rtn.distance = glm::length(ray.getOrigin() - rtn.intersectPoint);

    return rtn;
}

IntersectResponse Geometry::raySphereIntersection(Ray ray, std::shared_ptr<Sphere> sphere)
{
    return getIntersectPoint(ray, sphere);
}