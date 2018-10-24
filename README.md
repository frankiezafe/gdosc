# gdnative OSC

GDnative version of https://github.com/djiamnot/gdosc.

based on https://gitlab.com/frankiezafe/gdnative_template

## no headache process

just verifying that the basic example is compiling

`cd ~/forge.godot`

`git clone git@gitlab.com:frankiezafe/gdnative_template.git`

`cd gdnative_template`

`git submodule init && git submodule update`

`cd godot-cpp/`

`git submodule init && git submodule update`

`scons platform=linux headers_dir=godot_headers generate_bindings=yes`

`cd ../`

`scons platform=linux`