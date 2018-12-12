/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   oscreceiver.cpp
 * Author: frankiezafe
 * 
 * Created on December 10, 2018, 5:41 PM
 */

#include "oscreceiver.h"

using namespace osc;

void oscreceiver::_register_methods() {
    register_method("setup", &oscreceiver::setup);
}

oscreceiver::oscreceiver() :
_port(0),
_ready(false), _running(false) {
}

oscreceiver::~oscreceiver() {
}

bool oscreceiver::setup(unsigned int port) {

    if (port <= 0) {
        godot::Godot::print("Invalid osc::oscreceiver setup: invalid port");
        return false;
    }

    bool autorestart = false;
    if (_running) {
        stop();
        autorestart = true;
    }

    _port = port;

    _ready = true;

    if (autorestart) {
        return start();
    }

    return true;

}

bool oscreceiver::start() {

    if (!_ready) {
        godot::Godot::print("oscsender::oscreceiver, failed to start");
        return false;
    }

    stop();

    _running = true;
    return true;

}

void oscreceiver::stop() {

    _running = false;

}