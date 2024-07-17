#pragma once

#include "Lumina/Renderer/Camera.hpp"
#include "Lumina/Renderer/Shader.hpp"
#include "RenderCommand.hpp"
#include "RendererAPI.hpp"

namespace Lumina {

class Renderer {
public:
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

    inline static RendererAPI::API GetAPI() {
        return RendererAPI::GetAPI();
    }

private:
    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* m_SceneData;
};


} // namespace Lumina
