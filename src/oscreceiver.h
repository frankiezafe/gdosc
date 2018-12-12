/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   oscreceiver.h
 * Author: frankiezafe
 *
 * Created on December 10, 2018, 5:41 PM
 */

#ifndef OSCRECEIVER_H
#define OSCRECEIVER_H

#include <Godot.hpp>
#include <Node.hpp>

#include <OscTypes.h>
#include <UdpSocket.h>
#include <OscOutboundPacketStream.h>

namespace osc {

    class oscreceiver : public godot::GodotScript<godot::Node> {
        GODOT_CLASS(oscreceiver)

    public:

        static void _register_methods();

        oscreceiver();

        virtual ~oscreceiver();

        bool setup(unsigned int port);

        bool start();

        void stop();

    protected:

        int _port;
        bool _ready;
        bool _running;

    };

};

#endif /* OSCRECEIVER_H */

