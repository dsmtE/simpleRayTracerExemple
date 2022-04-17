#pragma once

#include <glm/glm.hpp>

struct Sphere {

public:
    glm::vec3 position;
    float radius;
    glm::u8vec3 color;

    Sphere(glm::vec3 p, float r, glm::u8vec3 c) : position(p), radius(r), color(c) {}
};

