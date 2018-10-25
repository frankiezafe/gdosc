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

### 2018/10/25

#### done

* Fix linking oscpack shared object files

#### pitfall

* SConstruct is definitely not cross-platform friendly, see comment in-file

#### Warnings

When loading the project, I get this in Godot's output window

```
 drivers/unix/net_socket_posix.cpp:301 - Method/Function Failed, returning: ERR_UNAVAILABLE
 modules/gdnative/gdnative.cpp:480 - No valid library handle, can't get symbol from GDNative object
 modules/gdnative/gdnative.cpp:386 - No valid library handle, can't terminate GDNative object
 Can't open dynamic library: /home/mis/src/gdnative_osc/demo/bin/x11/libgdosc.so. Error: /home/mis/src/gdnative_osc/demo/bin/x11/libgdosc.so: undefined symbol: nativescript_api
```

Also, in the console, possibly related to Frankie's *todo* point #4
```
ERROR: _load: Failed loading resource: res://bin/OSCreceiver.gdns
```

## links

* https://gamedevadventures.posthaven.com/using-c-plus-plus-and-gdnative-in-godot-part-1
* https://godotengine.org/qa/17007/possible-to-export-variables-to-editor-when-using-gdnative
* https://www.sisik.eu/blog/godot/gd-native-calling-gdscript-method-from-cpp-code
