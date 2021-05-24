#pragma once

#include "Eros/Core/Base.h"
#include "Logging/Log.h"
#include <filesystem>

#ifdef EROSIONSIM_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define EROSIONSIM_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { EROSIONSIM##type##ERROR(msg, __VA_ARGS__); EROSIONSIM_DEBUGBREAK(); } }
#define EROSIONSIM_INTERNAL_ASSERT_WITH_MSG(type, check, ...) EROSIONSIM_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define EROSIONSIM_INTERNAL_ASSERT_NO_MSG(type, check) EROSIONSIM_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", EROSIONSIM_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define EROSIONSIM_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define EROSIONSIM_INTERNAL_ASSERT_GET_MACRO(...) EROSIONSIM_EXPAND_MACRO( EROSIONSIM_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, EROSIONSIM_INTERNAL_ASSERT_WITH_MSG, EROSIONSIM_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define EROSIONSIM_ASSERT(...) EROSIONSIM_EXPAND_MACRO( EROSIONSIM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define EROSIONSIM_CORE_ASSERT(...) EROSIONSIM_EXPAND_MACRO( EROSIONSIM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define EROSIONSIM_ASSERT(...)
#define EROSIONSIM_CORE_ASSERT(...)
#endif