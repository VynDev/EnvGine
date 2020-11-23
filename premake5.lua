solution "EnvGine"
	configurations {"Debug", "Release"}

	project "EnvGine"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		files {"src/**.h", "src/**.cpp"}
		removefiles {"src/**.test.cpp"}
		targetdir "lib"

	configuration "Debug"
		defines {"DEBUG"}

	configuration "Release"
		defines {"NDEBUG"}
	
newaction {
	trigger = "clean",
	description = "clean the software",
	execute = function ()
		print("clean the build...")
		os.rmdir("./bin")
		os.rmdir("./obj")
		os.rmdir("./lib")
		os.remove("./Makefile")
		os.remove("./*.make")
		print("done.")
	end
}