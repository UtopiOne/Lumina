#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"
#include "Lumina/Events/ApplicationEvent.hpp"
#include "Window.hpp"

namespace Lumina
{

    class LUMINA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // To be defined in client
    Application* CreateApplication();

} // namespace Lumina