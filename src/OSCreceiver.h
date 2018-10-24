#ifndef GDOSC_RECEIVER_H
#define GDOSC_RECEIVER_H

#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <Godot.hpp>
#include <ClassDB.hpp>
#include <Ref.hpp>
#include <Engine.hpp>
#include <Object.hpp>
#include <MainLoop.hpp>
#include <Node.hpp>

#include <gdOscMessage.h>
#include <PacketListener.h>
#include <UdpSocket.h>
#include <OscPacketListener.h>
#include <OscPrintReceivedElements.h>
#include <OscReceivedElements.h>
#include <OSCmessage.h>

namespace gdosc {
	
	class OSCreceiver : public godot::Node, public osc::OscPacketListener {
		GODOT_SUBCLASS(OSCreceiver, godot::Node)
		//GODOT_CLASS(OSCreceiver)
		//GDCLASS(OSCreceiver, Node);

	public:
		
		OSCreceiver();
		~OSCreceiver();
		
		//gdnative mandatory
		static void _register_methods();
		
		//gdnative mandatory for node
		godot::Object* owner;

		/* Set native mode to true to prevent the object to turn OSC messages to gd Dicitionaries.
		* If set to true, use method getNextMessage( gdOscMessage& msg ) to retrieve messages.
		* @remark native_mode is set to false by default.
		*/
		void native_mode(bool enable);

		bool start();
		void stop();

		bool has_waiting_messages();
		godot::Ref<OSCmessage> get_next_message();

		/* USe this method to retrieve messages in C++. It is not exposed in gdscript, and
		* will return false if native_mode is not set to true.
		*/
		bool getNextMessage(gdOscMessage& msg);

		// setters
		bool set_port(int port);
		void set_max_queue(int max_queue);
		void set_autostart(bool autostart);
		void set_emit_signal(bool emit_signal);

		// getters
		const int& get_port() const { return _port; }
		int get_max_queue() const { return (int)_max_queue; }
		const bool& is_autostart() const { return _autostart; }
		const bool& is_emit_signal() const { return _emit_signal; }

	protected:
		
		void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);
		void _notification(int p_what);
		
		// use this when compiling in the engine directly
		//static void _bind_methods();

	private:
		
		std::mutex _lmutex;
		std::thread _lthread;
		UdpListeningReceiveSocket* _lsocket;

		int _port;
		std::size_t _max_queue;
		bool _autostart;
		bool _emit_signal;

		bool _native_mode;
		std::deque<gdOscMessage> _msg_queue;

		std::deque<OSCmessage>* _gd_queue_write;
		std::deque<OSCmessage>* _gd_queue_read;

		godot::Ref<OSCmessage> _gd_next_msg;

		void create_buffers();
		void purge_buffers();
		void swap_buffers();
		void check_queue();
		
	};

};
#endif