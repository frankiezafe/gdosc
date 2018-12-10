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
#include <UdpSocket.h>
#include <OscOutboundPacketStream.h>

namespace osc {

    class oscsender : public godot::GodotScript<godot::Node> {
        GODOT_CLASS(gd_script_node)
        
    public:
        
	static void _register_methods();
        
        oscsender();
        virtual ~oscsender();
        
    private:

    };
};

#endif /* OSCSENDER_H */

