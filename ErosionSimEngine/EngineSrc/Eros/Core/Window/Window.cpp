#include "ErosionSimPCH.h"
#include "Eros/Core/Window/Window.h"

#ifdef EROSIONSIM_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Eros
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef EROSIONSIM_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		EROSIONSIM_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}