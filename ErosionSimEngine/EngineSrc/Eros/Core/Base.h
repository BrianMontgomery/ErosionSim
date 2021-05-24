#pragma once

#include <memory>

#include "Eros/Core/PlatformDetection.h"

#ifdef EROSIONSIM_DEBUG
#if defined(EROSIONSIM_PLATFORM_WINDOWS)
#define EROSIONSIM_DEBUGBREAK() __debugbreak()
#elif defined(EROSIONSIM_PLATFORM_LINUX)
#include <signal.h>
#define EROSIONSIM_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define EROSIONSIM_ENABLE_ASSERTS
#else
#define EROSIONSIM_DEBUGBREAK()
#endif

#define EROSIONSIM_EXPAND_MACRO(x) x
#define EROSIONSIM_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define EROSIONSIM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Eros {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Eros/Core/Logging/Log.h"
#include "Eros/Core/Assert.h"