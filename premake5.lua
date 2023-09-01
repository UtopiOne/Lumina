workspace "Lumina"
    architecture "x64"
    toolset ("clang")

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Lumina"
    location "Lumina"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" ..outputdir.."/%{prj.name}")
    objdir ("bin-int/" ..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_SHARED",
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")
        }

    filter "system:linux"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LU_PLATFORM_LINUX",
            "LU_BUILD_SHARED",
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "LU_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LU_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "LU_DIST"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" ..outputdir.."/%{prj.name}")
    objdir ("bin-int/" ..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Lumina/src"
    }

    links
    {
        "Lumina"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HZ_PLATFORM_WINDOWS",
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")
        }

    filter "system:linux"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LU_PLATFORM_LINUX",
        }

        --postbuildcommands
        --{
        --    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")
        --}

    filter "configurations:Debug"
        defines "LU_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LU_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "LU_DIST"
        symbols "On"