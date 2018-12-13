#include "Camera.h"
#include "Ray.h"

Camera::Camera()
{
    projection = glm::perspective(glm::radians(45.0f), 3.0f / 4.0f, 0.1f, 100.f);
    view = glm::mat4(1);
}

/**
* createRay: 
* 1) translates positions to normalized device coordinates
* 2) Multiply positions by inverse projection matrix to convert to eye-space
* 3) Divide positions by W to convert from left to right-handed coordinate system
* 4) Multiply positions by inverse view matrix to convert world-space
* 5) Set ray origin to near plane position
* 6) Calculate and set ray direction using near and far plane coordinates
*/
Ray Camera::createRay(glm::vec3 pos)
{
    glm::vec4 origin;
    origin.x = (pos.x / (600.0f/2.0f)) - 1;
    origin.y = -((pos.y / (800.0f/2.0f)) - 1);
    origin.z = -1;
    origin.w = 1;

    glm::vec4 destination;
    destination.x = (pos.x / (600.0f/2.0f)) - 1;
    destination.y = -((pos.y / (800.0f/2.0f)) - 1);
    destination.z = 1;
    destination.w = 1;

    origin = glm::inverse(projection) * origin;
    destination = glm::inverse(projection) * destination;

    origin /= origin.w;
    destination /= destination.w;

    origin = glm::inverse(view) * origin;
    destination = glm::inverse(view) * destination;

    Ray ray;

    ray.setOrigin(glm::vec3(origin));

    glm::vec3 direction = glm::normalize(-glm::vec3(origin) + glm::vec3(destination));

    ray.setDirection(direction); 

    return ray;
}