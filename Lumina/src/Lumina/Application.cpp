#include "Application.hpp"

#include "Lumina/Events/ApplicationEvent.hpp"
#include "Lumina/Log.hpp"

namespace Lumina
{

Application::Application()
{
}
Application::~Application()
{
}

void Application::Run()
{
    WindowResizeEvent e(1280, 720);
    if (e.IsInCategory(EventCategoryApplication))
    {
        LU_TRACE(e);
    }
    if (e.IsInCategory(EventCategoryInput))
    {
        LU_TRACE(e);
    }

    while (true)
        ;
}

} // namespace Lumina