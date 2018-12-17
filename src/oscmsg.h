/*
 * See the LICENSE file at the root directory for license information
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
#include <PacketListener.h>
#include <OscReceivedElements.h>
#include <OscPacketListener.h>
#include <OscOutboundPacketStream.h>

namespace osc {

    class oscmsg_data {
    public:

        bool valid;
        godot::Dictionary data;

        oscmsg_data() : valid(false) {
        }

        oscmsg_data(
                const osc::ReceivedMessage& m,
                const IpEndpointName& rep) {

            data[ "address" ] = godot::String(m.AddressPattern());
            data[ "typetag" ] = godot::String(m.TypeTags());
            char endpointHost[IpEndpointName::ADDRESS_STRING_LENGTH];
            rep.AddressAsString(endpointHost);
            data[ "ip" ] = godot::String(endpointHost);
            data[ "port" ] = rep.port;

            godot::Array args;
            try {
                for (::osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin(); arg != m.ArgumentsEnd();
                        ++arg) {
                    if (arg->IsInt32()) {
                        args.append(arg->AsInt32Unchecked());
                    } else if (arg->IsFloat()) {
                        args.append(arg->AsFloatUnchecked());
                    } else if (arg->IsString()) {
                        args.append(godot::String(arg->AsStringUnchecked()));
                    } else if (arg->IsBool()) {
                        args.append(arg->AsBool());
                    } else {
                        args.append(false);
                    }
                }

            } catch (osc::Exception& e) {
                // any parsing errors such as unexpected argument types, or
                // missing arguments get thrown as exceptions.
                godot::String s = "oscmsg_data, error while parsing message ";
                s += m.AddressPattern();
                s += ": ";
                s += e.what();
                godot::Godot::print(s);
            }

            data[ "args" ] = args;
            data[ "arg_num" ] = args.size();
            valid = true;

        }

        oscmsg_data(const oscmsg_data& src) {
            valid = src.valid;
            data = src.data;
        }

        inline void operator=(const oscmsg_data& src) {
            valid = src.valid;
            data = src.data;
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
