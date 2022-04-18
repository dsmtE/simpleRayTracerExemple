#pragma once

#include "Sphere.hpp"

struct IntersectionResult {
    bool wasFound;
    const Sphere* sphere;
    float intersectionDistance;
};

class Ray {

public:
    glm::vec3 origin;
    glm::vec3 dir;

    Ray(glm::vec3 o, glm::vec3 d);

    IntersectionResult Intersect(const Sphere& sphere) const;
};



