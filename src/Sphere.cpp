#include "Sphere.h"
#include "Ray.h"
#include <iostream>

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

glm::vec3 Sphere::shade(Ray ray, glm::vec3 intersectPoint)
{
    glm::vec3 surfaceColor = color;

    //-------------------------------------------------------------------AMBIENT

    float ambientStrength = 0.1;
    glm::vec3 ambient = ambientStrength * color;

    //-------------------------------------------------------------------DIFFUSE
    glm::vec3 lightPos = glm::vec3(100, 100, 250);
 
    glm::vec3 lightDirection = glm::normalize(lightPos - intersectPoint);
    // glm::vec3 lightDirection = glm::normalize(intersectPoint - lightPos);

    glm::vec3 surfaceNormal = glm::normalize((intersectPoint - position) / radius);

    float diff = glm::max(glm::dot(surfaceNormal, lightDirection), 0.0f);

    //-------------------------------------------------------------------SPECULAR
    float specularStrength = 0.5f;
    glm::vec3 cameraPos = glm::vec3(300, 300, 0);
    glm::vec3 viewDir = -ray.getDirection();//glm::normalize(ray.getdirect - intersectPoint);
    glm::vec3 reflectDir = glm::normalize(glm::reflect(-lightDirection, surfaceNormal));
    float spec = glm::pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), 32);
    float specular = specularStrength * spec;

    surfaceColor = (ambient + diff + specular) * color;
    // surfaceColor = (ambient + diff) * color;
    // surfaceColor = diff * color;

    return glm::clamp(surfaceColor, glm::vec3(0,0,0), glm::vec3(1,1,1));
    // return color;
}