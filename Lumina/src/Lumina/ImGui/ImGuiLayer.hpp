#pragma once

#include "Lumina/Core.hpp"
#include "Lumina/Events/ApplicationEvent.hpp"
#include "Lumina/Events/Event.hpp"
#include "Lumina/Events/KeyEvent.hpp"
#include "Lumina/Events/MouseEvent.hpp"
#include "Lumina/Layer.hpp"

namespace Lumina {

class LUMINA_API ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;

    void Begin();
    void End();

private:
    float m_Time = 0.0f;
};

} // namespace Lumina
