#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <memory>

/*
* Struct to hold intersection data
*/
struct IntersectResponse
{
    bool hit;
    float distance;
    glm::vec3 intersectPoint;
};

class Ray;
class Sphere;

/**
* Class to handle geometry intersections
*/
class Geometry
{
    public:
    Geometry();
    
    IntersectResponse raySphereIntersection(Ray ray, std::shared_ptr<Sphere> sphere);
    IntersectResponse getIntersectPoint(Ray ray, std::shared_ptr<Sphere> sphere);
};

#endif