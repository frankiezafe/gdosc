# gdnative example


## no headache process

just verifying that the basic example is compiling

`cd ~/forge.godot`

`git clone git@gitlab.com:frankiezafe/gdnative_template.git`

`cd gdnative_template`

`clone https://github.com/GodotNativeTools/godot-cpp && git submodule init && git submodule update`

`cd godot-cpp/`

`git submodule init`

`git submodule update`

`scons platform=linux headers_dir=godot_headers generate_bindings=yes`

`cd ../`

`git clone https://github.com/GodotNativeTools/godot_headers && git submodule init && git submodule update`

`wget http://docs.godotengine.org/en/3.0/_downloads/SConstruct SConstruct`

`scons platform=linux`

and that should be ok for linux

now open godot engine v3.0 and import the demo project, it should behave as described in the [tutorial](http://docs.godotengine.org/en/3.0/tutorials/plugins/gdnative/gdnative-cpp-example.html#using-your-gdnative-module) 

## compiling godot engine (optional but usefull to ensure your engine is compiled with the same compiler as your lib)

`cd ~/forge.godot`
 
`git clone git@github.com:godotengine/godot.git godotengine-stable`
 
important for gdnative > master is ahead of the official release!

`git checkout -b 3.0`

scons will use gcc by default on linux, if you use the "use_llvm=yes" flag for compilation of the engine, use it for gdnative also!

`scons platform=x11`

## notes

### install llvm & clang (if using "use_llvm=yes" in scons)

`sudo apt install llvm clang`

### clear scons

`scons platform=x11 --config=force`

## links

* http://docs.godotengine.org/en/3.0/tutorials/plugins/gdnative/gdnative-cpp-example.html
* https://github.com/BastiaanOlij/gdnative_cpp_example/