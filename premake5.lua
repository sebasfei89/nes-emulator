workspace "NES"
    configurations { "Debug", "Release", "Dist" }
    architecture "x64"
    startproject "NES_Test"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
testvendordir = "NES_Test/vendor/"

IncludeDir = {}
-- IncludeDir["Catch2"] = testvendordir .. "Catch2"

-- Windows
Library = {}
-- Library["WinSock"] = "Ws2_32.lib"
-- Library["WinMM"] = "Winmm.lib"
-- Library["WinVersion"] = "Version.lib"
-- Library["BCrypt"] = "Bcrypt.lib"
-- Library["Dwmapi"] = "dwmapi.lib"

-- group "ThirdParty"
--     include "Feijoo/vendor/GLFW"
-- group ""

project "NES_Emulator"
    location "%{prj.name}"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    defines
    {
    }

    includedirs
    {
        "%{prj.name}/src"
    }

    links
    {
    }

    filter "system:windows"
        systemversion "latest"
        
        defines
        {
            -- "NES_BUILD_DLL",
            "_CRT_SECURE_NO_WARNINGS"
        }

        links
        {
        }
    
    filter "configurations:Debug"
        defines "NES_DEBUG"
        symbols "on"
        runtime "Debug"
    
    filter "configurations:Release"
        defines "NES_RELEASE"
        optimize "on"
        runtime "Release"
    
    filter "configurations:Dist"
        defines "NES_DIST"
        optimize "on"
        runtime "Release"

project "NES_Test"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    debugdir ("bin/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "NES_Emulator/src",
        testvendordir,
    }

    links { "NES_Emulator" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "NES_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NES_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "NES_DIST"
        runtime "Release"
        optimize "on"
