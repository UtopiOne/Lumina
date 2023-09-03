#include "GLFW/glfw3.h"
#include "LuPCH.hpp"
#include "Lumina/Core.hpp"
#include "Lumina/Log.hpp"
#include "X11Window.hpp"

namespace Lumina
{
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new X11Window(props);
    }

    X11Window::X11Window(const WindowProps& props)
    {
        Init(props);
    }

    X11Window::~X11Window()
    {
        Shutdown();
    }

    void X11Window::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        LU_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            LU_CORE_ASSERT(success, "Could not intialize GLFW!");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void X11Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void X11Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void X11Window::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool X11Window::IsVSync() const
    {
        return m_Data.VSync;
    }
} // namespace Lumina