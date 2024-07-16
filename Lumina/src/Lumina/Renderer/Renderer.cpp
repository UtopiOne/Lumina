#include "Renderer.hpp"

#include "LuPCH.hpp"
#include "Lumina/Renderer/RenderCommand.hpp"

namespace Lumina {

void Renderer::BeginScene() {
}

void Renderer::EndScene() {
}

void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

} // namespace Lumina
