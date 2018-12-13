#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere(glm::vec3 pos, int radius, glm::vec3 color)
{
    this->position = pos;
    this->radius = radius;
    this->color = color;
}

glm::vec3 Sphere::getPosition()
{
    return position;
}

float Sphere::getRadius()
{
    return radius;
}

/**
* shade:
* 1) Calculate ambient lighting
* 2) Calculate diffuse lighting
* 3) Calculate specular strength
* 4) return (ambient + diff + specular) * color 
*/
glm::vec3 Sphere::shade(Ray ray, glm::vec3 intersectPoint)
{
    glm::vec3 surfaceColor = color;

    //-------------------------------------------------------------------AMBIENT
    float ambientStrength = 0.1;
    glm::vec3 ambient = ambientStrength * color;

    //-------------------------------------------------------------------DIFFUSE
    glm::vec3 lightPos = glm::vec3(100, 100, 250);
 
    glm::vec3 lightDirection = glm::normalize(lightPos - intersectPoint);

    glm::vec3 surfaceNormal = glm::normalize((intersectPoint - position) / radius);

    float diff = glm::max(glm::dot(surfaceNormal, lightDirection), 0.0f);

    //-------------------------------------------------------------------SPECULAR
    float specularStrength = 0.5f;
    glm::vec3 viewDir = -ray.getDirection();
    glm::vec3 reflectDir = glm::normalize(glm::reflect(-lightDirection, surfaceNormal));
    float spec = glm::pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), 32);
    float specular = specularStrength * spec;

    surfaceColor = (ambient + diff + specular) * color;

    return glm::clamp(surfaceColor, glm::vec3(0,0,0), glm::vec3(1,1,1));
}