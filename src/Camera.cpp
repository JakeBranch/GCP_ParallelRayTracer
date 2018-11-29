#include "Camera.h"
#include "Ray.h" //Remove??

Camera::Camera()
{
    
}

Ray Camera::createRay(glm::vec3 pos)
{
    Ray ray;

    ray.setOrigin(pos);
    ray.setDirection(glm::vec3(0, 0, 1));

    return ray;
}