#pragma once

#include "Lumina/Renderer/Buffer.hpp"

namespace Lumina {

class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    void Bind() const;
    void Unbind() const;

    virtual void SetLayout(const BufferLayout& layout) override {
        m_Layout = layout;
    };
    virtual const BufferLayout& GetLayout() const override {
        return m_Layout;
    };

private:
    uint32_t m_RendererID;
    BufferLayout m_Layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    virtual void Bind() const;
    virtual void Unbind() const;

    virtual uint32_t GetCount() const {
        return m_Count;
    };

private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};

} // namespace Lumina
