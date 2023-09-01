#include "Lumina.hpp"
#include "Lumina/Application.hpp"

class Sandbox : public Lumina::Application
{
public:
    Sandbox()
    {
    }

    ~Sandbox()
    {
    }
};

Lumina::Application *Lumina::CreateApplication()
{
    return new Sandbox();
}
