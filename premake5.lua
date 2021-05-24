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

	toolset "v142"

	buildoptions
	{
		"-Zi",
		--"-WX",
		"-W4",
		"-FC",
		"-MT"
	}


outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = os.getenv("VULKAN_SDK")

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["glm"] = "vendor/glm"

--IncludeDir["stb"] = "vendor/stb"
--IncludeDir["tinyObjLoader"] = "vendor/tinyObjLoader"

IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["ImGuizmo"] = "vendor/ImGuizmo"

IncludeDir["spdlog"] = "vendor/spdlog/include"

IncludeDir["shaderc"] = "%{VULKAN_SDK}/Include/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{VULKAN_SDK}/Include/VulkanSDK-1.2.170.0-DebugLibs/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{VULKAN_SDK}/VulkanSDK-1.2.170.0-DebugLibs/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

group "Dependencies"
	include "vendor/GLFW"
	include "vendor/Glad"
	include "vendor/ImGui"

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

	files
	{
		"%{prj.name}/EngineSrc/**.h",
		"%{prj.name}/EngineSrc/**.cpp",
		"vendor/glm/glm/**.hpp",
		--"vendor/stb/stb/**.h",
		--basic tiny obj loader
		--"vendor/tinyObjLoader/tinyObjLoader/**.h",
		--optimized tiny obj loader
		--"vendor/tinyObjLoader/experimental/**.h",
		--"vendor/tinyObjLoader/experimental/**.hpp",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"

		--"assets/shaders/**.spv",
		--"assets/models/**.obj",
		--"assets/textures/**.jpg"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/EngineSrc",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		--"%{IncludeDir.stb}",
		--"%{IncludeDir.tinyObjLoader}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.VulkanSDK}"
		
	}

	libdirs { 
		"C:/VulkanSDK/1.1.121.2/Lib",
		"vendor/glfw/bin/Debug-windows-x86_64/glfw",
		"vendor/Glad/bin/Debug-windows-x86_64/Glad"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

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

		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Release"
		defines "EROSIONSIM_RELEASE"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter "configurations:Dist"
		defines "EROSIONSIM_DIST"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}


--App
project "ErosionSim"
	location "ErosionSim"
	kind "ConsoleApp"
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
		--"vendor/spdlog/include",
		"ErosionSimEngine/EngineSrc",
		"ErosionSim/AppSrc",
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