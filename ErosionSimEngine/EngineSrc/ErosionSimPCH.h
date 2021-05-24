#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Eros/Core/Base.h"
#include "Eros/Core/Logging/Log.h"
#include "Eros/Core/Debug/Instrumentor.h"

#ifdef EROSIONSIM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif