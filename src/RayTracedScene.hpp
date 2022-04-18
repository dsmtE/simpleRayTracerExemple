#pragma once

#include <vector>

#include "Sphere.hpp"
#include "Ray.hpp"

class RayTracedScene {
private:

    IntersectionResult CastRayThrough(const Ray& ray);

    Ray BuildRayFromPixelCoordinate(const size_t& x, const size_t& y, const size_t& width, const size_t& height);
    
    std::vector<Sphere> _spheres;
public:

    void AddSphere(const Sphere& sphere);
    void AddSphere(const glm::vec3& position, float radius, const glm::u8vec3& color);

    void RenderSceneInColorBuffer(glm::u8vec3* colorBuffer, const size_t& width, const size_t& height, const glm::u8vec3 clearColor = {0x00, 0x00, 0x00});
};
