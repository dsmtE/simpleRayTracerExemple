#pragma once

#include "Sphere.hpp"

class Ray {

public:
    glm::vec3 origin;
    glm::vec3 dir;

    Ray(glm::vec3 o, glm::vec3 d);

    bool Intersect(Sphere sphere, glm::vec3& IntersectPosition) const;
    bool Intersect(Sphere sphere, float& intersectionDistance) const;
};

