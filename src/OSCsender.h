#ifndef GDOSC_SENDER_H
#define GDOSC_SENDER_H

#include <ip/UdpSocket.h>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <Godot.hpp>
#include <ClassDB.hpp>
#include <Engine.hpp>
#include <Node.hpp>
#include <MainLoop.hpp>

#include <utils.h>
#include <gdOscMessage.h>
#include <OscOutboundPacketStream.h>

namespace gdosc {
	
	class OSCsender : public godot::Node {
		GODOT_SUBCLASS(OSCsender, godot::Node)
		//GODOT_CLASS(OSCsender)
		//GDCLASS(OSCsender, Node);

		public:
		
			OSCsender();
			~OSCsender();
		
			//gdnative mandatory
			static void _register_methods();
			
			//gdnative mandatory for node
			godot::Object* owner;

			bool start();
			void stop();

			// message related

			// construction of the message
			void msg_address(const godot::String& address);
			void msg_add_int(const int& i);
			void msg_add_real(const real_t& r);
			void msg_add_string(const godot::String& s);
			void msg_add_v2(const godot::Vector2& v);
			void msg_add_v3(const godot::Vector3& v);
			void msg_add_quat(const godot::Quat& q);
			void msg_add_transform(const godot::Transform& t);

			// send the message
			void msg_send();

			/* cleanup of the message, automatically called on send
			* if autoclear is enabled
			*/
			void msg_clear();

			// setters
			void set_ip(godot::String ip);
			void set_port(int port);
			void set_buffersize(int buffersize);
			void set_autostart(bool autostart);
			void set_autoclear(bool autoclear);

			// getters
			const godot::String& get_ip() const { return _ip; }
			const int& get_port() const { return _port; }
			const int& get_buffersize() const { return _buffersize; }
			const bool& is_autostart() const { return _autostart; }
			const bool& is_autoclear() const { return _autoclear; }
			const bool& is_ready() const { return _ready; }
			const bool& is_started() const { return _started; }

		protected:
		
			void _notification(int p_what);
			
			// use this when compiling in the engine directly
			//static void _bind_methods();
			
			bool init_osc(godot::String ip, int port);
			
		private:
			
			godot::String _ip;
			int _port;
			int _buffersize;
			bool _autostart;
			bool _autoclear;

			bool _ready;
			bool _started;

			IpEndpointName _message_target;
			std::unique_ptr<UdpTransmitSocket> _socket;

			gdOscMessage msg;
		
	};

};

#endif
