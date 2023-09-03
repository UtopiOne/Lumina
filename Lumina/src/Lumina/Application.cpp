#include "LuPCH.hpp"
#include "Application.hpp"

#include "Lumina/Events/ApplicationEvent.hpp"
#include "Lumina/Log.hpp"
#include "Lumina/Window.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace Lumina
{

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }
    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

} // namespace Lumina