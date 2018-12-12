/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   oscmsg.h
 * Author: frankiezafe
 *
 * Created on December 10, 2018, 5:52 PM
 */

#ifndef OSCMSG_H
#define OSCMSG_H

#include <Godot.hpp>
#include <Node.hpp>

#include <OscTypes.h>
#include <OscOutboundPacketStream.h>

namespace osc {

    class oscmsg : public godot::GodotScript<godot::Object> {
        GODOT_CLASS(oscmsg)

    public:

        static void _register_methods();

        oscmsg();

        virtual ~oscmsg();

        void buffer_size(int size);

        void address(godot::String address);

        void add(godot::Variant var);

        void close();

        inline bool ready() const {
            return _packet != 0;
        }

        inline const bool& closed() const {
            return _packet_closed;
        }

        const godot::PoolByteArray& data() const {
            return _array;
        }

        inline int size() const {
            return _buffer_size;
        }
        
        inline void is_oscmsg() const {}

    private:

        std::size_t _buffer_size;
        char* _buffer;
        osc::OutboundPacketStream* _packet;
        bool _packet_closed;
        
        godot::PoolByteArray _array;

        void reset();

    };

};

#endif /* OSCMSG_H */

