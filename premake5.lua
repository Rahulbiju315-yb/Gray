workspace "Opengl"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Gray"
	location "Gray"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	targetdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
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
		symbols "On"
	
	filter "configurations:Release"
		defines "GRAY_DEBUG"
		optimize "On"

	filter "configurations:Dist"
		defines "GRAY_DIST"
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
		"Gray/vendor/spdlog/include",
		"Gray/src"
	}

	links
	{
		"Gray"
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
		symbols "On"
	
	filter "configurations:Release"
		defines "GRAY_DEBUG"
		optimize "On"

	filter "configurations:Dist"
		defines "GRAY_DIST"
		optimize "On"