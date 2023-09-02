#pragma once

#include "Lumina/Log.hpp"
#include "Lumina/Application.hpp"

#ifdef LU_PLATFORM_WINDOWS

extern Lumina::Application* Lumina::CreateApplication();

int main(int argc, char** argv)
{
    Lumina::Log::Init();
    LU_CORE_WARN("Initialized Log!");
    LU_INFO("Welcome to Lumina!");

    auto app = Lumina::CreateApplication();
    app->Run();
    delete app;
}

#endif

#ifdef LU_PLATFORM_LINUX

extern Lumina::Application* Lumina::CreateApplication();

int main(int argc, char** argv)
{
    Lumina::Log::Init();
    LU_CORE_WARN("Initialized Log!");
    LU_INFO("Welcome to Lumina!");

    auto app = Lumina::CreateApplication();
    app->Run();
    delete app;
}

#endif