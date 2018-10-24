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


## devlog

### 2018/10/25

#### done

* all set methods are using Variant instead of typed arguments
* utils contains methods to check variant easily
* registration of methods and properties for gdnative
* adaptation of godot macros ( see GODOT_SUBCLASS )
* include and SConstruct adaptations, should be cross-platform

#### todo

* enable OSCreceiver signal in OSCreceiver.cpp, line 285 (crash at compilation)
* verify gdnlib & gdns in demo/bin/
* debug loadong in gdscript
* make OSCsender & OSCreceiver appears in the object selector in godot

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
