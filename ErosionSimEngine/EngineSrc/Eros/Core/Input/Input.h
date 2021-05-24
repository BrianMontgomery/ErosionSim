#pragma once

#include <glm/glm.hpp>

#include "Eros/Core/Input/KeyCodes.h"
#include "Eros/Core/Input/MouseCodes.h"

namespace Eros {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}