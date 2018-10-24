#include <iostream>

#include "Array.hpp"
#include "Resource.hpp"

#include "IpEndpointName.h"
#include "OscReceivedElements.h"

#ifndef GDOSC_MESSAGE_H
#define GDOSC_MESSAGE_H

namespace godot {

	class OSCmessage : public Resource {
		GDCLASS(OSCmessage, Resource);
		RES_BASE_EXTENSION("oscmessage");

	public:
		
		OSCmessage();
		OSCmessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);
		~OSCmessage();

		// getter
		_FORCE_INLINE_ const bool& is_valid() const { return _valid; }

		// getter, exposed in gdscript
		_FORCE_INLINE_ bool empty() const { return _arg_num < 1; }
		_FORCE_INLINE_ const String& ip() const { return _ip; }
		_FORCE_INLINE_ const int& port() const { return _port; }
		_FORCE_INLINE_ const String& address() const { return _address; }
		_FORCE_INLINE_ const String& typetag() const { return _typetag; }
		_FORCE_INLINE_ const int& arg_num() const { return _arg_num; }
		_FORCE_INLINE_ const Variant& arg(int p_idx) const { return _arguments[p_idx]; }

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
