#pragma once

#include "Eros/Core/Layers/Layer.h"

#include "Eros/Events/ApplicationEvent.h"
#include "Eros/Events/KeyEvent.h"
#include "Eros/Events/MouseEvent.h"

namespace Eros {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}