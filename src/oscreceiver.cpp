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

using namespace std;
using namespace osc;

void oscreceiver::_register_methods() {
    register_method("setup", &oscreceiver::setup);
    register_method("start", &oscreceiver::start);
}

oscreceiver::oscreceiver() :
_port(0),
_ready(false), _running(false),
_lsocket(0),
_max_queue(100),
_gd_queue_write(0),
_gd_queue_read(0) {
}

oscreceiver::~oscreceiver() {
    stop();
}

void oscreceiver::max_queue(int max_queue) {

    if (max_queue < 1) return;
    _max_queue = (std::size_t)max_queue;
    check_queue();

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
        godot::Godot::print("oscreceiver::start, receiver is not ready, "
                "call setup() first!");
        return false;
    }

    try {
        IpEndpointName name(IpEndpointName::ANY_ADDRESS, _port);
        _lsocket = new UdpListeningReceiveSocket(name, this);
    } catch (const std::exception& e) {
        godot::String s = "oscreceiver::start, failed to start on ";
        s += godot::String::num(_port);
        s += "\n";
        s += e.what();
        godot::Godot::print(s);
        return false;
    }

    stop();

    create_buffers();

    _lthread = std::thread([this] {
        while (_lsocket) {
            try {
                _lsocket->Run();
            } catch (std::exception& e) {
                godot::String s = "oscreceiver::_lthread, cannot listen ";
                s += e.what();
                godot::Godot::print(s);
            }
        }
        godot::String s = "oscreceiver::_lthread, thread is quitting on ";
        s += godot::String::num(_port);
        godot::Godot::print(s);
    });

    _lthread.detach();

    _running = true;
    godot::String s = "oscreceiver::start, successfully started on ";
    s += godot::String::num(_port);
    godot::Godot::print(s);
    return true;

}

void oscreceiver::stop() {

    if (_lsocket) {
        delete _lsocket;
        _lsocket = 0;
    }

    purge_buffers();

    _running = false;

    godot::String s = "oscreceiver::stop, stopped on ";
    s += godot::String::num(_port);
    godot::Godot::print(s);

}

void oscreceiver::create_buffers() {

    _lmutex.lock();
    if (!_gd_queue_write) {
        _gd_queue_write = new std::deque<oscmsg_data>();
        _gd_queue_read = new std::deque<oscmsg_data>();
    }
    _lmutex.unlock();

}

void oscreceiver::purge_buffers() {

    if (_gd_queue_write) {
        _gd_queue_write->clear();
        _gd_queue_read->clear();
        delete _gd_queue_write;
        delete _gd_queue_read;
        _gd_queue_write = 0;
        _gd_queue_read = 0;
    }

}

void oscreceiver::swap_buffers() {

    _lmutex.lock();
    std::deque<oscmsg_data>* tmp = _gd_queue_write;
    _gd_queue_write = _gd_queue_read;
    _gd_queue_read = tmp;
    _lmutex.unlock();

}

void oscreceiver::ProcessMessage(
        const osc::ReceivedMessage& m,
        const IpEndpointName& rep) {

    oscmsg_data msg( m, rep );
    if (msg.valid) {
      _lmutex.lock();
      _gd_queue_write->push_back(msg);
      check_queue();
      _lmutex.unlock();
    }
    
}

void oscreceiver::check_queue() {

    _lmutex.lock();
    if (_gd_queue_write && _gd_queue_write->size() > _max_queue) {
        _gd_queue_write->resize(_max_queue);
    }
    _lmutex.unlock();

}