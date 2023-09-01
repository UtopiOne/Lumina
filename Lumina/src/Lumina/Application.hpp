#pragma once

#include "Core.hpp"

namespace Lumina
{

class LUMINA_API Application
{
public:
    Application();
    virtual ~Application();

    void Run();
};

// To be defined in client
Application *CreateApplication();

} // namespace Lumina