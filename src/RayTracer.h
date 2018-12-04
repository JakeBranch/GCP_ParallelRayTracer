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
        void traceRay(Ray ray, glm::vec3 &color);

        void addSphere(std::shared_ptr<Sphere> sphere);

        void reset();

    private:
        std::list<std::shared_ptr<Sphere>> spheres; 
        std::shared_ptr<Geometry> geometry;

        int bounceLimit;
        int bounceCount;
};

#endif