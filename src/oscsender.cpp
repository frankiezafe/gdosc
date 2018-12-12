/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   oscsender.cpp
 * Author: frankiezafe
 * 
 * Created on December 10, 2018, 1:21 PM
 */

#include "oscsender.h"

using namespace godot;

void oscsender::_register_methods() {
    register_method("setup", &oscsender::setup);
    register_method("start", &oscsender::start);
    register_method("stop", &oscsender::stop);
    register_method("msg", &oscsender::msg);
    register_method("add", &oscsender::add);
    register_method("send", &oscsender::send);
}

oscsender::oscsender() :
_port(0), _buffer_size(1024),
_ready(false), _running(false),
_socket(0), _buffer(0), _packet(0), _packet_closed(false) {
}

oscsender::~oscsender() {

    reset_message();
    stop();

}

bool oscsender::setup(String ip, unsigned int port) {

    std::wstring ws = ip.unicode_str();
    std::string s(ws.begin(), ws.end());
    unsigned int p = port;

    if (s.empty()) {
        Godot::print("Invalid osc::oscsender setup: invalid ip");
        return false;
    }
    if (p <= 0) {
        Godot::print("Invalid osc::oscsender setup: invalid port");
        return false;
    }

    bool autorestart = false;
    if (_running) {
        stop();
        autorestart = true;
    }

    _ip = s;
    _port = p;
    _endpoint = ip + ":" + String::num(_port);

    _ready = true;

    if (autorestart) {
        return start();
    }

    return true;

}

bool oscsender::start() {

    if (!_ready) {
        Godot::print("oscsender::start, failed to start");
        return false;

    }

    stop();

    try {

        IpEndpointName _message_target = IpEndpointName(_ip.c_str(), _port);
        _socket = new UdpTransmitSocket(_message_target);
        Godot::print("oscsender::start, started successfully on " + _endpoint);

    } catch (std::exception& e) {

        Godot::print("oscsender::start, failed to start on " + _endpoint);
        //        std::cout << "scsender::stafailed to startrt, failed to starty" << e.what() << std::endl;

    }




    _running = true;
    return true;

}

void oscsender::stop() {

    if (_socket) {
        delete _socket;
        _socket = 0;
        Godot::print("oscsender::stop, socket closed on " + _endpoint);
    }
    _running = false;

}

void oscsender::reset_message() {

    if (_packet) {
        delete _packet;
        _packet = 0;
        _packet_closed = false;
    }
    if (_buffer) {
        delete[] _buffer;
        _buffer = 0;
    }

}

void oscsender::msg(godot::String address) {
    
    reset_message();
        
    std::wstring ws = address.unicode_str();
    std::string std_address(ws.begin(), ws.end());

    _buffer = new char[_buffer_size];
    _packet = new osc::OutboundPacketStream(_buffer, _buffer_size);
    (*_packet) << osc::BeginBundleImmediate
            << osc::BeginMessage(std_address.c_str());
    
}

void oscsender::add(godot::Variant var) {

    if (!_packet) {
        Godot::print("oscsender::add, message is not ready! "
                "call 'start_message' first!");
        return;
    }

    switch (var.get_type()) {
        case godot::Variant::Type::BOOL:
        {
            bool b = var;
            (*_packet) << b;
        }
            break;
        case godot::Variant::Type::STRING:
        case godot::Variant::Type::NODE_PATH:
        case godot::Variant::Type::_RID:
        case godot::Variant::Type::OBJECT:
        {
            godot::String s = var;
            (*_packet) << s.alloc_c_string();
        }
            break;
        case godot::Variant::Type::INT:
        {
            int i = var;
            (*_packet) << i;
        }
            break;
        case godot::Variant::Type::REAL:
        {
            float f = var;
            (*_packet) << f;
        }
            break;
        case godot::Variant::Type::VECTOR2:
        {
            godot::Vector2 v = var;
            (*_packet) << float( v.x);
            (*_packet) << float( v.y);
        }
            break;
        case godot::Variant::Type::VECTOR3:
        {
            godot::Vector3 v = var;
            (*_packet) << float( v.x);
            (*_packet) << float( v.y);
            (*_packet) << float( v.z);
        }
            break;
        case godot::Variant::Type::QUAT:
        {
            godot::Quat q = var;
            (*_packet) << float( q.x);
            (*_packet) << float( q.y);
            (*_packet) << float( q.z);
            (*_packet) << float( q.w);
        }
            break;
        case godot::Variant::Type::COLOR:
        {
            godot::Color c = var;
            (*_packet) << float( c.r );
            (*_packet) << float( c.g );
            (*_packet) << float( c.b );
            (*_packet) << float( c.a );
        }
            break;
        default:
            Godot::print("oscsender::add, unable to add "
                    "this kind of data!");
            break;

    }

}

void oscsender::send() {

    if (!_packet) {
        Godot::print("oscsender::send, message is not ready! "
                "call 'start_message' first!");
        return;
    }

    if (!_packet_closed) {
        (*_packet) << osc::EndMessage << osc::EndBundle;
        _packet_closed = true;
    }
    _socket->Send(_packet->Data(), _packet->Size());

}