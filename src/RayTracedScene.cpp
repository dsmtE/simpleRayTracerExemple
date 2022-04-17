#pragma once

#include "RayTracedScene.hpp"

#include <iostream>
#include <glm/gtc/constants.hpp>
#include <glm/vector_relational.hpp>

bool RayTracedScene::ThrowRayThrough(const Ray& ray, Sphere& hitSphere, glm::vec3& intersectPosition) {
    bool intersect = false;
    float intersectionDistance = std::numeric_limits<float>().infinity();

    for(Sphere s: _spheres) {
        float t;
        if(ray.Intersect(s, t) && t < intersectionDistance) {
            intersectionDistance = t;
            hitSphere = s;
            intersect = true;
        }
    }
    
    intersectPosition = ray.origin + intersectionDistance * ray.dir;

    return intersect;
}

Ray RayTracedScene::BuildRayFromPixelCoordinate(const size_t& x, const size_t& y, const size_t& width, const size_t& height) {
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
    
    float imageAspectRatio = width / (float)height; // assuming width > height 

    glm::vec3 cameraPosition = glm::vec3(0.f, 0.f, 0.f);
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

void RayTracedScene::RenderSceneInColorBuffer(glm::u8vec3* colorBuffer, const size_t& width, const size_t& height) {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            Ray r = BuildRayFromPixelCoordinate(x, y, width, height);

            Sphere hitSphere(glm::vec3(0.f, 0.f, 0.f), 0.f, glm::u8vec3(0, 0, 0));
            glm::vec3 intersectPosition;
            if(ThrowRayThrough(r, hitSphere, intersectPosition)) {
                colorBuffer[y*width+x] = hitSphere.color;
            }
        }
    }

}
