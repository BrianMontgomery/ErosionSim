#include "ErosionSimPCH.h"
#include "Eros/Renderer/RenderStructs/VertexArray.h"

#include "Eros/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Eros {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    EROSIONSIM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		EROSIONSIM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}