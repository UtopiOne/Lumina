#include "Shader.hpp"

#include "LuPCH.hpp"
#include "Lumina/Core.hpp"
#include "Lumina/Log.hpp"
#include "Lumina/Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Lumina {

Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {

    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        LU_CORE_ASSERT(false, "RendererAPI: None");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLShader(vertexSrc, fragmentSrc);
    }

    return nullptr;
}

} // namespace Lumina
