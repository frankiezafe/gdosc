#include "oscmsg.h"
#include "oscsender.h"
#include "oscreceiver.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    godot::register_class<osc::oscmsg>();
    godot::register_class<osc::oscsender>();
    godot::register_class<osc::oscreceiver>();
}