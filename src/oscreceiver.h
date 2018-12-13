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

#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <Godot.hpp>
#include <Node.hpp>

#include <OscTypes.h>
#include <UdpSocket.h>
#include <PacketListener.h>
#include <OscPacketListener.h>

#include "oscmsg.h"

namespace osc {

    class oscreceiver :
    public godot::GodotScript<godot::Node>,
    public osc::OscPacketListener {
        GODOT_CLASS(oscreceiver)

    public:

        static void _register_methods();

        oscreceiver();

        virtual ~oscreceiver();

        void max_queue(int max_queue);
       
        void avoid_duplicate( bool enabled );

        bool setup(unsigned int port);
        
        bool start();

        void stop();
        
        bool has_message();
        
        godot::Dictionary get_next();

    protected:

        int _port;
        bool _ready;
        bool _running;
        bool _swap_needed;
        bool _avoid_duplicate;

        // real processing stuff

        std::mutex _lmutex;
        std::thread _lthread;
        UdpListeningReceiveSocket* _lsocket;

        std::size_t _max_queue;

        std::deque<oscmsg_data>* _queue_write;
        std::deque<oscmsg_data>* _queue_read;
        std::size_t _qread_index;
        std::size_t _qread_len;
        
        void ProcessMessage(
                const osc::ReceivedMessage& m,
                const IpEndpointName& remoteEndpoint);

        void create_buffers();
        void purge_buffers();
        void swap_buffers();
        void check_queue();
        void purge_duplicates();

    };

};

#endif /* OSCRECEIVER_H */

