#include "Ray.h"

Ray::Ray()
{
    direction = glm::vec3(0, 0, 1);
    isPrimary = true;
    isShadow = false;
}

void Ray::setDirection(glm::vec3 dir)
{
    direction = dir;
}

void Ray::setOrigin(glm::vec3 orig)
{
    origin = orig;
}

glm::vec3 Ray::getDirection()
{
    return direction;
}

glm::vec3 Ray::getOrigin()
{
    return origin;
}