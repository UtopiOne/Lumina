#include "Buffer.hpp"

#include "LuPCH.hpp"

#include "Lumina/Core.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"
#include "Renderer.hpp"

namespace Lumina {

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        LU_CORE_ASSERT(false, "Renderer API: None");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
    }

    LU_CORE_ASSERT(false, "No renderer API set");
    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        LU_CORE_ASSERT(false, "Renderer API: None");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLIndexBuffer(indices, size);
    }

    LU_CORE_ASSERT(false, "No renderer API set");
    return nullptr;
}

} // namespace Lumina
