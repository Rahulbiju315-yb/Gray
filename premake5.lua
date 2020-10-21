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

include "Gray/vendor/glfw"
include "Gray/vendor/imgui"
include "Gray/vendor/imguiFileChooser"

project "Gray"
	location "Gray"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/src"
	}

	libdirs
	{
		"%{prj.name}/vendor/glew/lib/Release/x64/"
	}

	links
	{
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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines
		{
			"GRAY_PLATFORM_WINDOWS",
			"GRAY_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


	filter "configurations:Debug"
		defines "GRAY_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "GRAY_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GRAY_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"%{IncludeDirs.imguiFileChooser}",
		"Gray/src"
	}

	libdirs
	{
		"Gray/vendor/glew/lib/Release/x64/"
	}

	links
	{
		"Gray",
		"glew32s.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines
		{
			"GRAY_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "GRAY_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "GRAY_DEBUG"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GRAY_DIST"
		buildoptions "/MD"
		optimize "On"