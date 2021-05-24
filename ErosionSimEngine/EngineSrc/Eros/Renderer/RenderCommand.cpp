#include "ErosionSimPCH.h"
#include "Eros/Renderer/RenderCommand.h"

namespace Eros {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}