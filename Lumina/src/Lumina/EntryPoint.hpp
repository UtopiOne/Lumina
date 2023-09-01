#pragma once

#ifdef LU_PLATFORM_WINDOWS

extern Lumina::Application* Lumina::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Lumina::CreateApplication();
    app->Run();
    delete app;
}

#endif

#ifdef LU_PLATFORM_LINUX

extern Lumina::Application* Lumina::CreateApplication();

int main(int argc, char** argv)
{
    std::cout << "Welcome to Lumina on linux\n";
    auto app = Lumina::CreateApplication();
    app->Run();
    delete app;
}

#endif