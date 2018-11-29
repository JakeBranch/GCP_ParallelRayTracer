#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <memory>

struct IntersectResponse
{
    bool hit;
    float distance;
    glm::vec3 intersectPoint;
};

class Ray;
class Sphere;

class Geometry
{
    public:
    Geometry();

    glm::vec3 getClosestPoint(Ray ray, std::shared_ptr<Sphere> sphere);
    glm::vec3 getClosestIntersectionPoint(Ray ray, std::shared_ptr<Sphere> sphere, float distance);
    IntersectResponse raySphereIntersection(Ray ray, std::shared_ptr<Sphere> sphere);
};

#endif