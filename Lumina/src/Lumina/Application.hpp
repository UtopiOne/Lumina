#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"
#include "Lumina/Events/ApplicationEvent.hpp"
#include "Lumina/Layer.hpp"
#include "Lumina/LayerStack.hpp"
#include "Lumina/Renderer/Camera.hpp"
#include "Window.hpp"
#include "ImGui/ImGuiLayer.hpp"

#include "Lumina/Renderer/Buffer.hpp"
#include "Lumina/Renderer/Shader.hpp"
#include "Lumina/Renderer/VertexArray.hpp"

#include <memory>

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

    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Shader> m_Shader2;

    std::shared_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<VertexArray> m_SquareVA;

    OrthographicCamera m_Camera;

private:
    static Application* s_Instance;
};

// To be defined in client
Application* CreateApplication();

} // namespace Lumina
