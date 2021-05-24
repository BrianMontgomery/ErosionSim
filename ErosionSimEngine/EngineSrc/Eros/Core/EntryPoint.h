#pragma once
/* ========================================================================
   $File: EntryPoint.h$
   $Date: 3/22/2021$
   $Revision: 2$
   $Creator: Brian Montgomery $
   $Notice: (C) Copyright 2021 by Monty, Inc. All Rights Reserved. $
   ======================================================================== */


#include "Eros/Core/Base.h"
#include "Eros/Core/Application/Application.h"

#ifdef EROSIONSIM_PLATFORM_WINDOWS

extern Eros::Application *Eros::CreateApplication(Eros::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Eros::Log::Init();

	EROSIONSIM_PROFILE_BEGIN_SESSION("Startup", "ErosProfile-Startup.json");
	auto app = Eros::CreateApplication({ argc, argv });
	EROSIONSIM_PROFILE_END_SESSION();

	EROSIONSIM_PROFILE_BEGIN_SESSION("Runtime", "ErosProfile-Runtime.json");
	app->Run();
	EROSIONSIM_PROFILE_END_SESSION();

	EROSIONSIM_PROFILE_BEGIN_SESSION("Shutdown", "ErosProfile-Shutdown.json");
	delete app;
	EROSIONSIM_PROFILE_END_SESSION();
}

#endif