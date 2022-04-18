#pragma once

#include "RayTracedScene.hpp"

#include <iostream>
#include <glm/gtc/constants.hpp>

IntersectionResult RayTracedScene::CastRayThrough(const Ray& ray) {
    float intersectionDistance = std::numeric_limits<float>().infinity();
    const Sphere* hitSphere = nullptr;
    
    for(const Sphere& s: _spheres) {
        const auto intersection = ray.Intersect(s);
        if(intersection.wasFound && intersection.intersectionDistance < intersectionDistance) {
            intersectionDistance = intersection.intersectionDistance;
            hitSphere = intersection.sphere;
        }
    }

    return {hitSphere != nullptr, hitSphere, intersectionDistance};
}

Ray RayTracedScene::BuildRayFromPixelCoordinate(const size_t& x, const size_t& y, const size_t& width, const size_t& height) {
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
    
    float imageAspectRatio = width / (float)height; // assuming width > height 

    glm::vec3 cameraPosition = glm::vec3(0.f);
    float cameraFovAngle = 90.f;
    
    glm::vec2 normalizeDeviceCoordinate = glm::vec2((x+0.5f)/width, (y+0.5f)/height);

    glm::vec2 pixelScreenCoordinate = 2.f * normalizeDeviceCoordinate - 1.f;
    pixelScreenCoordinate.y *= -1.0f; // flip y axis

    pixelScreenCoordinate.x *= imageAspectRatio;

    // correct with fov
    pixelScreenCoordinate *= glm::tan(cameraFovAngle / 2.f * glm::pi<float>() / 180.f);

    return Ray(cameraPosition, glm::vec3(pixelScreenCoordinate.x, pixelScreenCoordinate.y, -1.f)-cameraPosition);
}

void RayTracedScene::AddSphere(const Sphere& sphere) {
    _spheres.push_back(sphere);
}

void RayTracedScene::AddSphere(const glm::vec3& position, float radius, const glm::u8vec3& color) {
    _spheres.emplace_back(position, radius, color);
}

void RayTracedScene::RenderSceneInColorBuffer(glm::u8vec3* colorBuffer, const size_t& width, const size_t& height, const glm::u8vec3 clearColor) {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            const Ray r = BuildRayFromPixelCoordinate(x, y, width, height);
            const auto intersection = CastRayThrough(r);
            // The position of the intersection can be computed like that if needed
            // glm::vec3 intersectPosition = ray.origin + ray.dir * intersection.intersectionDistance;
            colorBuffer[y*width+x] = intersection.wasFound ? intersection.sphere->color : clearColor;
        }
    }

}
