#include "App.hpp"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

App::App(GLFWwindow* window) : _resolutionFactor(1.0f), _colorBuffer(nullptr) {

    // Generate texture
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    BuildScene();
    
    glm::ivec2 framebufferSize = FramebufferSize(window);
    InitColorBuffer(framebufferSize.x, framebufferSize.y);
}

void App::InitColorBuffer(const size_t& width, const size_t& height) {

    if (_colorBuffer != nullptr) {
        delete _colorBuffer;
        _colorBuffer = nullptr;
    }

    _colorBufferWidth = static_cast<size_t>(width*_resolutionFactor);
    _colorBufferHeight = static_cast<size_t>(height*_resolutionFactor);
    _colorBuffer = new glm::u8vec3[_colorBufferWidth * _colorBufferHeight];
    RenderSceneToColorBuffer();
}

void App::BuildScene() {
    _scene.AddSphere({0.f, 0.f, -4.f}, 1.f, {0x00, 0x00, 0xff});
    _scene.AddSphere({1.f, 0.f, -3.f}, 1.f, {0xff, 0x00, 0xff});
}

void App::RenderSceneToColorBuffer() {
    _scene.RenderSceneInColorBuffer(_colorBuffer, _colorBufferWidth, _colorBufferHeight);
}

void App::Render(GLFWwindow* window) {
    
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    RenderSceneToColorBuffer();

    // Get frameBuffer size
    glm::ivec2 framebufferSize = FramebufferSize(window);
    // Set up orphographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, framebufferSize.x, framebufferSize.y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // Update the texture with our data buffer
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(_colorBufferWidth), static_cast<GLsizei>(_colorBufferHeight), 0, GL_RGB, GL_UNSIGNED_BYTE, glm::value_ptr(*_colorBuffer));

    // Render the texture on the screen
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0); glVertex2i(0, 0);
        glTexCoord2d(1,0); glVertex2i(framebufferSize.x, 0);
        glTexCoord2d(1,1); glVertex2i(framebufferSize.x, framebufferSize.y);
        glTexCoord2d(0,1); glVertex2i(0, framebufferSize.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
}

void App::key_callback(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/) {
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/) {
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/) {
}

void App::cursor_position_callback(double /*xpos*/, double /*ypos*/) {

}

void App::size_callback(int width, int height) {
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);

    InitColorBuffer(width, height);
}

glm::ivec2 App::FramebufferSize(GLFWwindow* window) {
    glm::ivec2 size(0);
    glfwGetFramebufferSize(window, &size.x, &size.y);
    return size;
}