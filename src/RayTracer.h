#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm/glm.hpp>
#include <list>
#include <memory>

class Geometry;
class Sphere;
class Ray;

class RayTracer
{
    public:
        RayTracer();
        glm::vec3 traceRay(Ray ray);

        void addSphere(std::shared_ptr<Sphere> sphere);

    private:
        std::list<std::shared_ptr<Sphere>> spheres; 
        std::shared_ptr<Geometry> geometry;
};

#endif