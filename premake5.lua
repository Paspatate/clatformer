workspace "Platformer"
   configurations { "Debug", "Release" }
   location "build"
   architecture "x86_64"

project "platformer"
   kind "ConsoleApp"
   language "C"
   targetdir "bin"

   files { "src/**.h", "src/**.c" }

   files { "Dependencies/glad/src/gl.c",
           "Dependencies/stb/src/stb_image.c"}

   includedirs { "Dependencies/glad/include",
                 "Dependencies/stb/include",
                 "include"}

   filter "system:not windows"
        links {"glfw", "m"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      optimize "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
