#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Ray;

class Camera
{
    public:
        Camera();

        Ray createRay(glm::vec3 pos);
};

#endif