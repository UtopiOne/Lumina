#include "Application.hpp"

#include "LuPCH.hpp"
#include "Lumina/Input.hpp"
#include "Lumina/Renderer/Buffer.hpp"
#include "Lumina/Renderer/Shader.hpp"
#include "Lumina/Renderer/Renderer.hpp"
#include "Lumina/Renderer/VertexArray.hpp"

#include "Lumina/Renderer/Camera.hpp"

namespace Lumina {

Application* Application::s_Instance = nullptr;

Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
    LU_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(LU_BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    m_VertexArray.reset(VertexArray::Create());

    float vertices[7 * 3] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f,                                       //
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f  //
    };

    std::shared_ptr<VertexBuffer> triangleVB;
    triangleVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float4, "a_Color"}};
    triangleVB->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(triangleVB);

    unsigned int indices[3] = {0, 1, 2};
    std::shared_ptr<IndexBuffer> triangleIB;
    triangleIB.reset(IndexBuffer::Create(indices, 3));
    triangleIB->Bind();
    m_VertexArray->SetIndexBuffer(triangleIB);

    m_SquareVA.reset(VertexArray::Create());
    float verticesSquare[3 * 4] = {-0.75f, -0.75f, 0.0f, 0.75f, -0.75f, 0.0f, 0.75f, 0.75f, 0.0f, -0.75f, 0.75f, 0.0f};
    std::shared_ptr<VertexBuffer> squareVB;
    squareVB.reset(VertexBuffer::Create(verticesSquare, sizeof(verticesSquare)));
    squareVB->SetLayout({
        {ShaderDataType::Float3, "a_Position"},
    });
    m_SquareVA->AddVertexBuffer(squareVB);

    unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<IndexBuffer> squareIB;
    squareIB.reset(IndexBuffer::Create(squareIndices, 6));
    squareIB->Bind();
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string vertexSrc = R"(
        #version 330 core
    
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjectionMatrix;

        out vec4 v_Color;

        void main() {
            v_Color = a_Color;
            gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
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

    std::string vertexSrc2 = R"(
        #version 330 core
    
        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_ViewProjectionMatrix;

        void main() {
            gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc2 = R"(
        #version 330 core
    
        layout(location = 0) out vec4 color;

        void main() {
            color = vec4(0.5, 0.5, 0.5, 1.0);
        }
    )";

    m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
    m_Shader2.reset(Shader::Create(vertexSrc2, fragmentSrc2));
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
        RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
        RenderCommand::Clear();

        m_Camera.SetRotation(45.0f);

        Renderer::BeginScene(m_Camera);

        Renderer::Submit(m_Shader2, m_SquareVA);
        Renderer::Submit(m_Shader, m_VertexArray);

        Renderer::EndScene();

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
