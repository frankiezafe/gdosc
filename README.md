# gdnative OSC

GDNative OSC is an addon that enables reception and emission of [OSC](http://opensoundcontrol.org/introduction-osc?) messages in [Godot game engine](https://godotengine.org/).

The code will compile into a dynamic library, easy to load and use in godot projects.

[tech demo video](https://peertube.mastodon.host/videos/watch/41b6c455-3278-4e85-9ee6-e6d99bb4eae7)

* GDnative version of https://github.com/djiamnot/gdosc.
* based on https://gitlab.com/frankiezafe/gdnative_template

## about OSC

Open Sound Control (OSC) is a network protocol commonly used in digital arts, stage and live multimedia performances to exchange information between softwares. Based on UDP protocol, it ensures fast communication and nearly no knowledge about network management.

This addon is based on the cross-platorm OSC lib [oscpack](http://www.rossbencina.com/code/oscpack).

[OSC official website](http://opensoundcontrol.org)

## structure

### demo/

contains a ready to use godot 3.0.6 project, see [video](https://peertube.mastodon.host/videos/watch/41b6c455-3278-4e85-9ee6-e6d99bb4eae7)

library is located in demo/bin/, once the project compiled

### demo-pd/

contains a simple [puredata](http://puredata.info/) patch that emits OSC messages

### src/

contains the sources of the library

## compilation

### no headache process

#### linux

``` bash
    git clone https://gitlab.com/frankiezafe/gdosc.git
    cd gdosc
    git submodule init && git submodule update
    cd godot-cpp/
    git submodule init && git submodule update
    scons platform=linux headers_dir=godot_headers generate_bindings=yes
    cd ../
    scons platform=linux
```

#### osx

``` git clone https://gitlab.com/frankiezafe/gdosc.git
    cd gdosc
    git submodule init && git submodule update
    cd godot-cpp/
    git submodule init && git submodule update
    scons platform=linux headers_dir=godot_headers generate_bindings=yes
    cd ../
    scons platform=linux
```

#### windows 10 64bits + vs 2017

``` git clone https://gitlab.com/frankiezafe/gdosc.git
    cd gdosc
    git submodule init && git submodule update
    cd godot-cpp/
    git submodule init && git submodule update
    scons platform=windows headers_dir=godot_headers generate_bindings=yes
    cd ../
    scons platform=windows
```

for other windows / vs version, refer to https://gitlab.com/frankiezafe/gdnative_template
