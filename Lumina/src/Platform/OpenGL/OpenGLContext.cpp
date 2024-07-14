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
}

void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}

} // namespace Lumina
