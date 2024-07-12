#include "LuPCH.hpp"
#include "Application.hpp"

#include "Lumina/Core.hpp"
#include "Lumina/Events/ApplicationEvent.hpp"
#include "Lumina/Events/Event.hpp"
#include "Lumina/Events/KeyEvent.hpp"
#include "Lumina/Layer.hpp"
#include "Lumina/Log.hpp"
#include "Lumina/Window.hpp"
#include "Lumina/Input.hpp"

#include <glad/glad.h>
#include <functional>
#include <GLFW/glfw3.h>

namespace Lumina
{

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        LU_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(LU_BIND_EVENT_FN(Application::OnEvent));

        unsigned int id;
        glGenVertexArrays(1, &id);
    }
    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(LU_BIND_EVENT_FN(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0.1, 0.1, 0.1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            auto [x, y] = Input::GetMousePosition();
            LU_CORE_TRACE("{0}, {1}", x, y);


            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

} // namespace Lumina
