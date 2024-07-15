#pragma once

#include <cstdint>
namespace Lumina {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() {};
    virtual void Unbind() {};

    static VertexBuffer* Create(float* vertices, uint32_t size);
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() {};
    virtual void Unbind() {};

    virtual uint32_t GetCount() const = 0;

    static IndexBuffer* Create(uint32_t* indices, uint32_t size);
};

} // namespace Lumina
