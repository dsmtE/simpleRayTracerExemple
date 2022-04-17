#pragma once
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <glm/glm.hpp>

#include "RayTracedScene.hpp"

class App {
public:

    App(GLFWwindow* window);

    void RenderSceneToColorBuffer();
    void Render(GLFWwindow* window);

    // window inputs callback
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

    static glm::ivec2 FramebufferSize(GLFWwindow* window);

private:
    void InitColorBuffer(const size_t& width, const size_t& height);
    void BuildScene();

    GLuint _textureId;

    size_t _colorBufferWidth;
    size_t _colorBufferHeight;
    glm::u8vec3* _colorBuffer;

    // used to render less pixel that the size of the window(framebuffer)
    float _resolutionFactor;

    RayTracedScene _scene;
};