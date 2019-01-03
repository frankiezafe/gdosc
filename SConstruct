#!python
import os

target = ARGUMENTS.get("target", "debug")
platform = ARGUMENTS.get("platform", "windows")
bits = ARGUMENTS.get("bits", 64)

final_lib_path = 'demo/addons/gdosc/bin/'
ip_path = 'oscpack/ip/posix/'

# This makes sure to keep the session environment variables on windows, 
# that way you can run scons in a vs 2017 prompt and it will find all the required tools
env = Environment()

def add_sources(sources, directory):
	for file in os.listdir(directory):
		if file.endswith('.cpp'):
			sources.append(directory + '/' + file)

if platform == "osx":
	env.Append(CCFLAGS = ['-g','-O3', '-arch', 'x86_64', '-std=c++14'])
	env.Append(LINKFLAGS = ['-arch', 'x86_64'])
	final_lib_path = final_lib_path + 'osx/'

elif platform == "linux":
	env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++14'])
	final_lib_path = final_lib_path + 'x11/'

elif platform == "windows":
	env = Environment(ENV = os.environ)
	if target == "debug":
		env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '/MDd', '-DOSC_HOST_LITTLE_ENDIAN'])
	else:
		env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '/MD', '-DOSC_HOST_LITTLE_ENDIAN'])
	ip_path = 'oscpack/ip/win32/'
	final_lib_path = final_lib_path + 'win' + str(bits) + '/'

env.Append(CPPPATH=['.', 'src/', 'oscpack/', 'oscpack/osc/', 'oscpack/ip/', ip_path, "godot-cpp/godot_headers/", 'godot-cpp/include/', 'godot-cpp/include/core/'])
env.Append(LIBPATH="godot-cpp/bin")

if platform == "windows":
	env.Append(LIBS=["godot-cpp" + "." + platform + "." + str(bits), "ws2_32", "wsock32", "winmm"])
else:
	env.Append(LIBS=["godot-cpp" + "." + platform + "." + str(bits)])

sources = []
add_sources(sources, "src")
add_sources(sources, "oscpack/osc")
add_sources(sources, "oscpack/ip")
add_sources(sources, ip_path)

library = env.SharedLibrary(target=final_lib_path + 'libgdosc', source=sources)
Default(library)