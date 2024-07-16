#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "LuPCH.hpp"
#include "Lumina/Input.hpp"
#include "Lumina/Renderer/Buffer.hpp"
#include "Lumina/Renderer/Shader.hpp"

namespace Lumina {

Application* Application::s_Instance = nullptr;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
        return GL_FLOAT;
    case ShaderDataType::Float2:
        return GL_FLOAT;
    case ShaderDataType::Float3:
        return GL_FLOAT;
    case ShaderDataType::Float4:
        return GL_FLOAT;
    default:
        return GL_NONE;
    }
}

Application::Application() {
    LU_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(LU_BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    float vertices[7 * 3] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f,                                       //
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f  //
    };


    m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float4, "a_Color"}};
    m_VertexBuffer->SetLayout(layout);

    uint32_t index = 0;
    for (const auto& element : m_VertexBuffer->GetLayout()) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              m_VertexBuffer->GetLayout().GetStride(),
                              (const void*)element.Offset);
        index++;
    }


    unsigned int indices[3] = {0, 1, 2};
    m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
    m_IndexBuffer->Bind();

    std::string vertexSrc = R"(
        #version 330 core
    
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec4 v_Color;

        void main() {
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core
    
        layout(location = 0) out vec4 color;

        in vec4 v_Color;

        void main() {
            color = v_Color;
        }
    )";

    m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
}

Application::~Application() {
}

void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(LU_BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::Run() {
    while (m_Running) {
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Bind();
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

        for (Layer* layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (Layer* layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        auto [x, y] = Input::GetMousePosition();

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
}

} // namespace Lumina
