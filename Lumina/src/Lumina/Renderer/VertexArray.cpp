#include "LuPCH.hpp"

#include "VertexArray.hpp"

#include "Lumina/Core.hpp"

#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Lumina {

VertexArray* VertexArray::Create() {
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        LU_CORE_ASSERT(false, "RendererAPI::None");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexArray();
    }

    LU_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
}

} // namespace Lumina
