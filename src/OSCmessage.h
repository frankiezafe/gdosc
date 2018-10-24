#ifndef GDOSC_MESSAGE_H
#define GDOSC_MESSAGE_H

#include <iostream>

#include <Godot.hpp>
#include <ClassDB.hpp>
#include <Array.hpp>
#include <Resource.hpp>

#include <IpEndpointName.h>
#include <OscReceivedElements.h>

namespace gdosc {

	class OSCmessage : public godot::Resource {
		//GODOT_SUBCLASS(OSCmessage, godot::Resource)
		GODOT_CLASS(OSCmessage)
		//GDCLASS(OSCmessage, Resource);
		//RES_BASE_EXTENSION("oscmessage");
	
	public:
		
		OSCmessage();
		OSCmessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);
		~OSCmessage();
		
		//gdnative mandatory
		static void _register_methods();
		
		// getter
		const bool& is_valid() const { return _valid; }
		
		// getter, exposed in gdscript
		bool empty() const { return _arg_num < 1; }
		const godot::String& ip() const { return _ip; }
		const int& port() const { return _port; }
		const godot::String& address() const { return _address; }
		const godot::String& typetag() const { return _typetag; }
		const int& arg_num() const { return _arg_num; }
		const godot::Variant& arg(int p_idx) const { return _arguments[p_idx]; }
		
		// operators
		void copy(const OSCmessage& src);
	
	protected:
		
		// use this when compiling in the engine directly
		//static void _bind_methods();
		
		const godot::Array& arguments() const { return _arguments; }
	
	private:
		
		bool _valid;
		godot::String _ip;
		int _port;
		godot::String _address;
		godot::String _typetag;
		int _arg_num;
		godot::Array _arguments;
		
	};

};

#endif
