#include "LuPCH.hpp"

#include "RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Lumina {

RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
