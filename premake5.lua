workspace "LearningOpenGL"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["ImGui"] = "Application/vendor/imgui"
IncludeDir["GLFW"]  = "Application/vendor/GLFW/include"
IncludeDir["GLEW"]  = "Application/vendor/GLEW/include"
IncludeDir["STB"]   = "Application/vendor/STB"
IncludeDir["GLM"]   = "Application/vendor/GLM"


-- Projects
group "Dependencies"
	include "Application/vendor/imgui"
group ""

project "Application"
	location "Application"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/STB/stb_image.h",
		"%{prj.name}/vendor/STB/stb_image.cpp",
		"%{prj.name}/vendor/GLM/glm/**.hpp",
		"%{prj.name}/vendor/GLM/glm/**.inl",
		"%{prj.name}/tests/**.h",
		"%{prj.name}/tests/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.STB}",
		"%{prj.name}/tests"		
	}

	filter "system:macosx"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
		}

-- linking with GLFW
	libdirs {
		"%{prj.name}/vendor/GLFW/lib-macos",
		"%{prj.name}/vendor/GLEW/lib/"

	}
	links {
		"glfw3",
		"OpenGL.framework",
		"IOKit.framework",
		"CoreFoundation.framework",
		"Cocoa.framework",
		"GLEW",
		"ImGui"
	}	
	filter "configurations:Debug"
		defines "GL_DEBUG"
		symbols "On"


	filter "configurations:Release"
		defines "GL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GL_DIST"
		optimize "On"