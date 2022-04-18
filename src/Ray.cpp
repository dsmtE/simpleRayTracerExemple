#include "Ray.hpp"

#include <glm/gtx/intersect.hpp>

Ray::Ray(glm::vec3 o, glm::vec3 d) : origin(o), dir(d) {}

IntersectionResult Ray::Intersect(const Sphere& sphere) const {
    float intersectionDistance;
    bool wasFound = glm::intersectRaySphere(origin, glm::normalize(dir), sphere.position, sphere.radius*sphere.radius, intersectionDistance);

    return {wasFound, &sphere, intersectionDistance};
}