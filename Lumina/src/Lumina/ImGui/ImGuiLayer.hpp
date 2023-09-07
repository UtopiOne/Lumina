#pragma once

#include "Lumina/Core.hpp"
#include "Lumina/Events/Event.hpp"
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
        float m_Time = 0.0f;
    };

} // namespace Lumina