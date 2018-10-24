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

### 2018/10/25

#### gdscript

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
* https://godotengine.org/qa/17007/possible-to-export-variables-to-editor-when-using-gdnative
* https://www.sisik.eu/blog/godot/gd-native-calling-gdscript-method-from-cpp-code
