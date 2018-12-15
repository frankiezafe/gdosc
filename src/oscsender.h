/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   oscsender.h
 * Author: frankiezafe
 *
 * Created on December 10, 2018, 1:21 PM
 */

#ifndef OSCSENDER_H
#define OSCSENDER_H

#include <Godot.hpp>
#include <Node.hpp>

#include "oscmsg.h"

namespace osc {

    class oscsender : public godot::GodotScript<godot::Node> {
        GODOT_CLASS(oscsender)

    public:

        static void _register_methods();

        oscsender();
        
        virtual ~oscsender();

        bool setup(godot::String ip, unsigned int port);

        bool start();

        void stop();
        
        void msg( godot::String address );
        
        void add( godot::Variant var );
        
        void send();

    protected:

        std::string _ip;
        int _port;
        std::size_t _buffer_size;
        godot::String _endpoint;
        bool _ready;
        bool _running;
        
        UdpTransmitSocket* _socket;
        
        char* _buffer;
        osc::OutboundPacketStream* _packet;
        bool _packet_closed;
        
        void reset_message();

    };
};

#endif /* OSCSENDER_H */

