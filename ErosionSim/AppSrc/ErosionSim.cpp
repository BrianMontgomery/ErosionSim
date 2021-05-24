#include <ErosionSimEngine.h>
#include <Eros/Core/EntryPoint.h>

//#include "EditorLayer.h"
namespace Eros {
	class ErosionSim : public Application
	{
	public:
		ErosionSim(ApplicationCommandLineArgs args)
			: Application("ErosionSim", args)
		{
			//PushLayer(new EditorLayer());
		}

		~ErosionSim()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new ErosionSim(args);
	}
}