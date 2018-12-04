#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray
{
    public:
        Ray();

        void setDirection(glm::vec3 dir);
        void setOrigin(glm::vec3 orig);

        glm::vec3 getOrigin();
        glm::vec3 getDirection();

        bool isPrimary;

    private:
        glm::vec3 direction;
        glm::vec3 origin; 
};

#endif