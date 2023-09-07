#include "Lumina.hpp"
#include "Lumina/Application.hpp"
#include "Lumina/Events/Event.hpp"
#include "Lumina/ImGui/ImGuiLayer.hpp"
#include "Lumina/Layer.hpp"
#include "Lumina/Log.hpp"

class ExampleLayer : public Lumina::Layer
{
public:
    ExampleLayer() : Lumina::Layer("Example")
    {
    }

    void OnUpdate() override
    {
        LU_INFO("ExampleLayer::Update");
    }

    void OnEvent(Lumina::Event& event) override
    {
        LU_TRACE("{0}", event);
    }
};

class Sandbox : public Lumina::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Lumina::ImGuiLayer());
    }

    ~Sandbox()
    {
    }
};

Lumina::Application* Lumina::CreateApplication()
{
    return new Sandbox();
}
