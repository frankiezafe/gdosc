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
#include <UdpSocket.h>
#include <OscReceivedElements.h>
#include <OscOutboundPacketStream.h>

namespace osc {

    class oscmsg_data {
    public:

        bool valid;
        godot::String ip;
        int port;
        godot::String address;
        godot::String typetag;
        int arg_num;
        godot::Array arguments;

        oscmsg_data() : valid(false), port(0), arg_num(0) {
        }

        oscmsg_data(
                const osc::ReceivedMessage& m,
                const IpEndpointName& rep) {

            address = godot::String(m.AddressPattern());
            typetag = godot::String(m.TypeTags());
            char endpointHost[IpEndpointName::ADDRESS_STRING_LENGTH];
            rep.AddressAsString(endpointHost);
            ip = godot::String(endpointHost);
            port = rep.port;

            try {

                for (::osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin(); arg != m.ArgumentsEnd();
                        ++arg) {
                    if (arg->IsInt32()) {
                        arguments.append(arg->AsInt32Unchecked());
                    } else if (arg->IsFloat()) {
                        arguments.append(arg->AsFloatUnchecked());
                    } else if (arg->IsString()) {
                        arguments.append(godot::String(arg->AsStringUnchecked()));
                    } else if (arg->IsBool()) {
                        arguments.append(arg->AsBool());
                    }
                }

            } catch (osc::Exception& e) {
                // any parsing errors such as unexpected argument types, or
                // missing arguments get thrown as exceptions.
                std::cout << "error while parsing message: " << m.AddressPattern() << ": " << e.what() << "\n";
            }

            arg_num = arguments.size();
            valid = true;

        }

        oscmsg_data(const oscmsg_data& src) {
            valid = src.valid;
            ip = src.ip;
            port = src.port;
            address = src.address;
            typetag = src.typetag;
            arg_num = src.arg_num;
            arguments = src.arguments;
        }

        inline void operator=(const oscmsg_data& src) {
            valid = src.valid;
            ip = src.ip;
            port = src.port;
            address = src.address;
            typetag = src.typetag;
            arg_num = src.arg_num;
            arguments = src.arguments;
        }

    };

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

        inline void is_oscmsg() const {
        }

    protected:

        std::size_t _buffer_size;
        char* _buffer;
        osc::OutboundPacketStream* _packet;
        bool _packet_closed;

        godot::PoolByteArray _array;

        void reset();

    };

};

#endif /* OSCMSG_H */

