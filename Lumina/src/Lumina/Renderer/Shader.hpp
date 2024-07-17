#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <string>

namespace Lumina {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

    static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
};

} // namespace Lumina
