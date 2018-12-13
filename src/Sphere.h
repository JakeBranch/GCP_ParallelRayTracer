#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

class Ray;

/**
*   Class to store sphere data and handle sphere shading
*/
class Sphere
{
    public:
        Sphere(glm::vec3 pos, int radius, glm::vec3 color);

        glm::vec3 shade(Ray ray, glm::vec3 intersectPoint);

        glm::vec3 getPosition();
        float getRadius();

    private:
        glm::vec3 position;
        float radius;
        glm::vec3 color;
};

#endif