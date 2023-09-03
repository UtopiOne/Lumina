#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"

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
    Application* CreateApplication();

} // namespace Lumina