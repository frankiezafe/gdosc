#ifndef GDOSC_MESSAGE_H
#define GDOSC_MESSAGE_H

#include <iostream>

#include "Array.hpp"
#include "Resource.hpp"

#include "IpEndpointName.h"
#include "OscReceivedElements.h"

namespace godot {

	class OSCmessage : public godot::Resource {
		GODOT_SUBCLASS(OSCmessage, godot::Resource);
		//GODOT_CLASS(OSCmessage);
		//GDCLASS(OSCmessage, Resource);
		//RES_BASE_EXTENSION("oscmessage");
	
	public:
		
		OSCmessage();
		OSCmessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);
		~OSCmessage();
		
		// getter
		inline const bool& is_valid() const { return _valid; }
		
		// getter, exposed in gdscript
		inline bool empty() const { return _arg_num < 1; }
		inline const String& ip() const { return _ip; }
		inline const int& port() const { return _port; }
		inline const String& address() const { return _address; }
		inline const String& typetag() const { return _typetag; }
		inline const int& arg_num() const { return _arg_num; }
		inline const Variant& arg(int p_idx) const { return _arguments[p_idx]; }
		
		// operators
		void copy(const OSCmessage& src);
	
	protected:
		
		static void _bind_methods();
		const Array& arguments() const { return _arguments; }
	
	private:
		
		bool _valid;
		String _ip;
		int _port;
		String _address;
		String _typetag;
		int _arg_num;
		Array _arguments;
		
	};

};

#endif
