#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Ray;

/**
* Class to handle creation of rays
*/
class Camera
{
    public:
        Camera();

        Ray createRay(glm::vec3 pos);

    private:
        glm::mat4 projection;
        glm::mat4 view;
};

#endif