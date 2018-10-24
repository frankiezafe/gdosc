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


## errors

### new gdnative script inheriting from OSCreceiver

result:

	ERROR: get_symbol: No valid library handle, can't get symbol from GDNative object
	   At: modules/gdnative/gdnative.cpp:480.

	ERROR: init_library: No nativescript_init in "res://bin/x11/libgdosc.so" found
	   At: modules/gdnative/nativescript/nativescript.cpp:1493.

	ERROR: get_symbol: No valid library handle, can't get symbol from GDNative object
	   At: modules/gdnative/gdnative.cpp:480.

	ERROR: terminate: No valid library handle, can't terminate GDNative object
	   At: modules/gdnative/gdnative.cpp:386.

	ERROR: open_dynamic_library: Can't open dynamic library: /home/frankiezafe/forge.godot/gdnative_osc/demo/bin/x11/libgdosc.so. Error: /home/frankiezafe/forge.godot/gdnative_osc/demo/bin/x11/libgdosc.so: undefined symbol: _ZTI9UdpSocket
	   At: drivers/unix/os_unix.cpp:415.

### new gdscript

gdscript :

`receiver = load("res://bin/OSCreceiver.gdns").new()`

result:

	ERROR: poll: res://bin/OSCreceiver.gdns:9 - Parse Error: Can't load cached ext-resource #1
	   At: scene/resources/scene_format_text.cpp:587.

	ERROR: load: Condition ' err != OK ' is true. returned: RES()
	   At: core/io/resource_loader.cpp:155.

	ERROR: _load: Failed loading resource: res://bin/OSCreceiver.gdns
	   At: core/io/resource_loader.cpp:192.



## links

* https://gamedevadventures.posthaven.com/using-c-plus-plus-and-gdnative-in-godot-part-1
