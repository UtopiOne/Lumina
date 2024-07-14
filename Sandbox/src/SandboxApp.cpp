#include <Lumina.hpp>

#include <imgui.h>

class ExampleLayer : public Lumina::Layer {
public:
    ExampleLayer() : Lumina::Layer("Example") {
    }

    void OnUpdate() override {
        // LU_INFO("ExampleLayer::Update");
    }

    virtual void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

    void OnEvent(Lumina::Event& event) override {
        // LU_TRACE("{0}", event);
    }
};

class Sandbox : public Lumina::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {
    }
};

Lumina::Application* Lumina::CreateApplication() {
    return new Sandbox();
}
