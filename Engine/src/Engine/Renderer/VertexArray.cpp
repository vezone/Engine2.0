#include "engine_pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ENGINE_CORE_ASSERT(0, "RenderAPI: none");
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLVertexArray();
			}
		}
		ENGINE_CORE_ASSERT(0, "unknown render API !");
		return nullptr;
	}
}