#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"
#include "Lumina/Events/ApplicationEvent.hpp"
#include "Lumina/Layer.hpp"
#include "Lumina/LayerStack.hpp"
#include "Window.hpp"
#include "ImGui/ImGuiLayer.hpp"

namespace Lumina {

class LUMINA_API Application {
public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    inline static Application& Get() {
        return *s_Instance;
    }
    inline Window& GetWindow() {
        return *m_Window;
    }

private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    bool m_Running = true;
    LayerStack m_LayerStack;

private:
    static Application* s_Instance;
};

// To be defined in client
Application* CreateApplication();

} // namespace Lumina
