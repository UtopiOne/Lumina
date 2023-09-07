#pragma once

#include "Lumina/Core.hpp"
#include "Lumina/Events/ApplicationEvent.hpp"
#include "Lumina/Events/Event.hpp"
#include "Lumina/Events/KeyEvent.hpp"
#include "Lumina/Events/MouseEvent.hpp"
#include "Lumina/Layer.hpp"

namespace Lumina
{

    class LUMINA_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizedEvent(WindowResizeEvent& e);

    private:
        float m_Time = 0.0f;
    };

} // namespace Lumina