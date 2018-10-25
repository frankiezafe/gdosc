#!/usr/bin/env python
import os

target = ARGUMENTS.get("target", "debug")
platform = ARGUMENTS.get("platform", "windows")
bits = ARGUMENTS.get("bits", 64)

final_lib_path = 'demo/bin/'
ip_path = 'src/oscpack/ip/posix/'

# This makes sure to keep the session environment variables on windows,
# that way you can run scons in a vs 2017 prompt and it will find all the required tools
env = Environment()

if platform == "windows":
    # modifying oscpack ip folder
	# ip_path = 'src/oscpack/ip/win32/'
    ip_system_type = 'win32'
    env = Environment(ENV = os.environ)

def add_sources(sources, directory):
	for file in os.listdir(directory):
		if file.endswith('.cpp'):
			sources.append(directory + '/' + file)

if platform == "osx":
	env.Append(CCFLAGS = ['-g','-O3', '-arch', 'x86_64', '-std=c++14'])
	env.Append(LINKFLAGS = ['-arch', 'x86_64'])
    # ip_system_type = 'osx'

	final_lib_path = final_lib_path + 'osx/'

elif platform == "linux":
    env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++14'])
    ip_system_type = "posix"

    final_lib_path = final_lib_path + 'x11/'

elif platform == "windows":
	if target == "debug":
	    env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '-MDd'])
	else:
		env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '-MD'])

	final_lib_path = final_lib_path + 'win' + str(bits) + '/'

env.Append(CPPPATH=['.', 'src/', 'src/oscpack/', 'src/oscpack/osc/', 'src/oscpack/ip/', ip_path, "godot-cpp/godot_headers/", 'godot-cpp/include/', 'godot-cpp/include/core/'])
env.Append(LIBPATH="godot-cpp/bin")
# env.Append(LIBS=["godot-cpp" + "." + platform + "." + str(bits)])

# add oscpack
env.Append(LIBPATH="#src/oscpack")
env.Append( CPPPATH=["src/oscpack",'src/oscpack/osc', "src/oscpack/ip"])
env.Append(LIBPATH="#src/oscpack/ip")
# the following line is definitely not platform independent.
env.Append(LINKFLAGS=[
    "src/oscpack/osc/OscOutboundPacketStream.os",
    "src/oscpack/osc/OscTypes.os",
    "src/oscpack/ip/{}/UdpSocket.os".format(ip_system_type)
])

env.Append(LIBPATH='#src/oscpack/ip/{0}' .format(ip_system_type))

sources = []
add_sources(sources, "src")
# add_sources(sources, "src/oscpack/")
# add_sources(sources, "src/oscpack/osc/")
# add_sources(sources, "src/oscpack/ip/")
# add_sources(sources, ip_path)

library = env.SharedLibrary(target=final_lib_path + 'libgdosc', source=sources)
Default(library)
