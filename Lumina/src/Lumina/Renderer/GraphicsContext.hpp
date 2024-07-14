#pragma once

namespace Lumina {

class GraphicsContext {
public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};
} // namespace Lumina
