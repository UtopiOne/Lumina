#pragma once

#include "Lumina/Renderer/Shader.hpp"

namespace Lumina {

class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    virtual ~OpenGLShader();

    virtual void Bind() const;
    virtual void Unbind() const;

private:
    uint32_t m_RendererID;
};

} // namespace Lumina
