#pragma once

#include <string>

namespace Lumina {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const {};
    virtual void Unbind() const {};

    static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
};

} // namespace Lumina
