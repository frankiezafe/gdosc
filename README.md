# gdnative OSC

GDNative OSC is an addon that enables reception and emission of [OSC](http://opensoundcontrol.org/introduction-osc?) messages in [Godot game engine](https://godotengine.org/).

The code will compile into a dynamic library, easy to load and use in godot projects.

[tech demo video](https://peertube.mastodon.host/videos/watch/41b6c455-3278-4e85-9ee6-e6d99bb4eae7)

* GDnative version of https://github.com/djiamnot/gdosc.
* based on https://gitlab.com/frankiezafe/gdnative_template

## structure

### demo/

contains a ready to use godot 3.0.6 project, see [video](https://peertube.mastodon.host/videos/watch/41b6c455-3278-4e85-9ee6-e6d99bb4eae7)

library is located in demo/bin/, once the project compiled

### demo-pd/

contains a simple [puredata](http://puredata.info/) patch that emits OSC messages

### src/

contains the sources of the library

## about OSC

Open Sound Control (OSC) is a network protocol commonly used in digital arts, stage and live multimedia performances to exchange information between softwares. Based on UDP protocol, it ensures fast communication and nearly no knowledge about network management.

This addon is based on the cross-platorm OSC lib [oscpack](http://www.rossbencina.com/code/oscpack).

[OSC official website](http://opensoundcontrol.org)

## compilation

### no headache process (linux)

    git clone https://gitlab.com/frankiezafe/gdnative_osc.git
    cd gdnative_template
    git submodule init && git submodule update
    cd godot-cpp/
    git submodule init && git submodule update
    scons platform=linux headers_dir=godot_headers generate_bindings=yes
    cd ../
    scons platform=linux

### no headache process (windows)

    git clone https://gitlab.com/frankiezafe/gdnative_osc.git
    cd gdnative_template
    git submodule init && git submodule update
    cd godot-cpp/
    git submodule init && git submodule update
    call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\vcvars64.bat"
    scons platform=windows headers_dir=godot_headers generate_bindings=yes
    cd ../
    call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\vcvars64.bat"
    scons platform=windows

## devlog

### 2018/12/13

#### done

* compilation fixed
* classes oscsender and oscreceiver ready to use

#### todo

* finish the oscmsg (osc message) class to prepare messages in gdscript instead

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

`receiver = load("res://bin/OSCreceiver.gdns").new()`

result:

	ERROR: poll: res://bin/OSCreceiver.gdns:9 - Parse Error: Can't load cached ext-resource #1
	   At: scene/resources/scene_format_text.cpp:587.

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
