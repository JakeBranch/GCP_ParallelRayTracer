#include "Camera.h"
#include "Ray.h" //Remove??

#include <glm/ext.hpp>

Camera::Camera()
{
    
}

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

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 3.0f / 4.0f, 0.1f, 100.f); 
    origin = glm::inverse(projection) * origin;
    destination = glm::inverse(projection) * destination;

    origin /= origin.w;
    destination /= destination.w;

    glm::mat4 view(1);
    origin = glm::inverse(view) * origin;
    destination = glm::inverse(view) * destination;
        
    Ray ray;
    ray.setOrigin(glm::vec3(origin));
    glm::vec3 direction = glm::normalize(-glm::vec3(origin) + glm::vec3(destination));
    ray.setDirection(direction);
    
    return ray;
}