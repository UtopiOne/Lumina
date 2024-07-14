#include "GLFW/glfw3.h"

#include "LuPCH.hpp"
#include "X11Window.hpp"
#include "Lumina/Events/Event.hpp"
#include "Lumina/Events/KeyEvent.hpp"
#include "Lumina/Events/MouseEvent.hpp"

#include "Lumina/Core.hpp"
#include "Lumina/Log.hpp"
#include "Lumina/Events/ApplicationEvent.hpp"
#include "Platform/OpenGL/OpenGLContext.hpp"


namespace Lumina {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description) {
    LU_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window* Window::Create(const WindowProps& props) {
    return new X11Window(props);
}

X11Window::X11Window(const WindowProps& props) {
    Init(props);
}

X11Window::~X11Window() {
    Shutdown();
}

void X11Window::Init(const WindowProps& props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    LU_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);


    if (!s_GLFWInitialized) {
        glfwSetErrorCallback(GLFWErrorCallback);
        int success = glfwInit();
        LU_CORE_ASSERT(success, "Could not intialize GLFW!");

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

    m_Context = new OpenGLContext(m_Window);

    m_Context->Init();


    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        WindowResizeEvent event(width, height);
        data.Width = width;
        data.Height = height;
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
        }
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
        }
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });
}

void X11Window::Shutdown() {
    glfwDestroyWindow(m_Window);
}

void X11Window::OnUpdate() {
    glfwPollEvents();
    m_Context->SwapBuffers();
    glfwSwapBuffers(m_Window);
}

void X11Window::SetVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.VSync = enabled;
}

bool X11Window::IsVSync() const {
    return m_Data.VSync;
}

} // namespace Lumina
