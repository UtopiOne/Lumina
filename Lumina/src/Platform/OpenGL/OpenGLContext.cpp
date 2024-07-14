#include "OpenGLContext.hpp"

#include "LuPCH.hpp"
#include "Lumina/Core.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Lumina {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
    LU_CORE_ASSERT(m_WindowHandle, "Window Handle is null");
}

void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    LU_CORE_ASSERT(status, "Failed to initialize Glad!");

    const char* glVendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const char* glRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    LU_CORE_INFO("OpenGL info:");
    LU_CORE_INFO("  Vendor: {0}", glVendor);
    LU_CORE_INFO("  Renderer: {0}", glRenderer);
    LU_CORE_INFO("  Version: {0}", glVersion);
}

void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}

} // namespace Lumina
