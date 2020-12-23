workspace "Opengl"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["glfw"] = "Gray/vendor/glfw/include"
IncludeDirs["spdlog"] = "Gray/vendor/spdlog/include"
IncludeDirs["imgui"] = "Gray/vendor/imgui/"
IncludeDirs["imguiFileChooser"] = "Gray/vendor/imguiFileChooser/"
IncludeDirs["dirent"] = "Gray/vendor/imgui/"
IncludeDirs["glm"] = "Gray/vendor/glm/"
IncludeDirs["glew"] = "Gray/vendor/glew/include/"
IncludeDirs["assimp"] = "Gray/vendor/assimp/include/"

include "Gray/vendor/glfw"
include "Gray/vendor/imgui"
include "Gray/vendor/imguiFileChooser"

project "Gray"
	location "Gray"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "grpch.h"
	pchsource "Gray/src/grpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDirs.spdlog}",
		"%{IncludeDirs.glfw}",
		"%{IncludeDirs.dirent}",
		"%{IncludeDirs.imgui}",
		"%{IncludeDirs.imguiFileChooser}",
		"%{IncludeDirs.glew}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.assimp}",
		"%{prj.name}/src"
	}

	libdirs
	{
		"%{prj.name}/vendor/glew/lib/Release/x64/",
		"%{prj.name}/vendor/assimp/lib/Release/"
	}

	links
	{
		"assimp-vc142-mt.lib",
		"glew32s.lib",
		"GLFW",
		"opengl32",
		"imgui",
		"imguiFileChooser"
	}

	defines
	{
		"GLEW_STATIC"
	}
	
	filter "system:windows"
		systemversion "10.0.17763.0"

		defines
		{
			"GRAY_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "GRAY_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "GRAY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GRAY_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDirs.spdlog}",
		"%{IncludeDirs.glfw}",
		"%{IncludeDirs.dirent}",
		"%{IncludeDirs.imgui}",
		"%{IncludeDirs.glew}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.imguiFileChooser}",
		"%{IncludeDirs.assimp}",
		"Gray/src"
	}

	libdirs
	{
		"Gray/vendor/glew/lib/Release/x64/",
		"Gray/vendor/assimp/lib/Release/"
	}

	links
	{
		"assimp-vc142-mt.lib",
		"Gray",
		"glew32s.lib",
		"opengl32"
	}

	filter "system:windows"
		systemversion "10.0.17763.0"

		defines
		{
			"GRAY_PLATFORM_WINDOWS",
			"GLEW_STATIC"
		}

	filter "configurations:Debug"
		defines "GRAY_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "GRAY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GRAY_DIST"
		runtime "Release"
		optimize "on"