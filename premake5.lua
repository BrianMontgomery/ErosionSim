workspace "ErosionSim"
	architecture "x86_64"
	startproject "ErosionSim"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	disablewarnings 
	{
		"4201", "4100", "4189"
	}

	toolset "clang"

	buildoptions
	{
		--"-Zi",
		--"-WX",
		--"-W4",
		--"-FC"
	}


outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/glad/include"
IncludeDir["glm"] = "vendor/glm"
--IncludeDir["stb"] = "vendor/stb"
--IncludeDir["ImGui"] = "vendor/imgui"
--IncludeDir["tinyObjLoader"] = "vendor/tinyObjLoader"

group "Dependencies"
	include "vendor/GLFW"
	include "vendor/Glad"
	--include "vendor/imgui"

group ""

project "ErosionSimEngine"
	location "ErosionSimEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "ErosionSimPCH.h"
	pchsource "%{prj.name}/EngineSrc/ErosionSimPCH.cpp"

	entrypoint "WinMain"

	files
	{
		"%{prj.name}/EngineSrc/**.h",
		"%{prj.name}/EngineSrc/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
		--"vendor/stb/stb/**.h",
		--basic tiny obj loader
		--"vendor/tinyObjLoader/tinyObjLoader/**.h",
		--optimized tiny obj loader
		--"vendor/tinyObjLoader/experimental/**.h",
		--"vendor/tinyObjLoader/experimental/**.hpp",

		--"assets/shaders/**.spv",
		--"assets/models/**.obj",
		--"assets/textures/**.jpg"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs
	{
		"%{prj.name}/EngineSrc",
		"%{prj.name}/EngineSrc/Platform",
		"%{prj.name}/EngineSrc/ErosionSim",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}"
		--"%{IncludeDir.stb}",
		--"%{IncludeDir.ImGui}",
		--"%{IncludeDir.tinyObjLoader}"
	}

	libdirs { 
		"vendor/glfw/bin/Debug-windows-x86_64/glfw"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		--"ImGui",-
		"glfw.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"UNICODE",
		}

	filter "configurations:Debug"
		defines "EROSIONSIM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EROSIONSIM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EROSIONSIM_DIST"
		runtime "Release"
		optimize "on"


--App
project "ErosionSim"
	location "ErosionSim"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/AppSrc/**.h",
		"%{prj.name}/AppSrc/**.cpp",

		--"assets/shaders/**.spv",
		--"assets/models/**.obj",
		--"assets/textures/**.jpg"
	}

	includedirs
	{
		"vendor/spdlog/include",
		"ErosionSimEngine/EngineSrc",
		"ErosionSim/AppSrc",
		"vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"ErosionSimEngine"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "EROSIONSIM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EROSIONSIM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EROSIONSIM_DIST"
		runtime "Release"
		optimize "on"