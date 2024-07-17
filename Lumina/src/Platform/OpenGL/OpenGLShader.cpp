#include "OpenGLShader.hpp"

#include "LuPCH.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Lumina {

OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* source = vertexSrc.c_str();
    glShaderSource(vertexShader, 1, &source, nullptr);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        LU_CORE_ERROR("Vertex shader compilation failure!");
        LU_CORE_ERROR("{0}", infoLog.data());

        LU_CORE_ASSERT(false, "Vertex shader compilation failure!");

        // In this simple m_RendererID, we'll just leave
        return;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = fragmentSrc.c_str();
    glShaderSource(fragmentShader, 1, &source, nullptr);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        LU_CORE_ERROR("Fragment shader compilation failure!");
        LU_CORE_ERROR("{0}", infoLog.data());

        LU_CORE_ASSERT(false, "Fragment shader compilation failure!");

        // In this simple m_RendererID, we'll just leave
        return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a m_RendererID.
    // Get a m_RendererID object.
    m_RendererID = glCreateProgram();

    // Attach our shaders to our m_RendererID
    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);

    // Link our m_RendererID
    glLinkProgram(m_RendererID);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

        // We don't need the m_RendererID anymore.
        glDeleteProgram(m_RendererID);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.
        LU_CORE_ERROR("Shader linking failure!");
        LU_CORE_ERROR("{0}", infoLog.data());

        LU_CORE_ASSERT(false, "Shader linking failure!");

        // In this simple m_RendererID, we'll just leave
        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(m_RendererID, vertexShader);
    glDetachShader(m_RendererID, fragmentShader);
}

OpenGLShader::~OpenGLShader() {
    glDeleteProgram(m_RendererID);
}

void OpenGLShader::Bind() const {
    glUseProgram(m_RendererID);
}

void OpenGLShader::Unbind() const {
    glUseProgram(0);
}

void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
    GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace Lumina
