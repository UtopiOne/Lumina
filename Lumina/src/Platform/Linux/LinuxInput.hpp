#pragma once

#include "LuPCH.hpp"

#include "Lumina/Core.hpp"
#include "Lumina/Input.hpp"

namespace Lumina {

class LinuxInput : public Input {
protected:
    virtual bool IsKeyPressedImpl(int keycode) override;
    virtual bool IsMouseButtonPressedImpl(int button) override;
    virtual std::pair<float, float> GetMousePositionImpl() override;
    virtual float GetMouseXImpl() override;
    virtual float GetMouseYImpl() override;
};

} // namespace Lumina
