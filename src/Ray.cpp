#include "Ray.hpp"

#include <glm/gtx/intersect.hpp>

Ray::Ray(glm::vec3 o, glm::vec3 d) : origin(o), dir(d) {}

bool Ray::Intersect(Sphere sphere, glm::vec3& position) const {
    glm::vec3 intersectionNormal;
    return glm::intersectRaySphere(origin, glm::normalize(dir), sphere.position, sphere.radius*sphere.radius, position, intersectionNormal);
}

bool Ray::Intersect(Sphere sphere, float& intersectionDistance) const {
    return glm::intersectRaySphere(origin, glm::normalize(dir), sphere.position, sphere.radius*sphere.radius, intersectionDistance);
}