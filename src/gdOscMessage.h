#ifndef _OSCMESSAGE_
#define _OSCMESSAGE_

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "Reference.hpp"
#include "String.hpp"

#include "gdOscArg.h"

namespace godot {

	class gdOscMessage {
	
	public:
		
		gdOscMessage();
		~gdOscMessage();

		void clear();
		void setAddress(const std::string& address);
		void setTypetag(const std::string& typetag);
		std::string getAddress() const;
		std::string getRemoteIp() const;
		std::string getTypetag() const;
		void setRemoteEndpoint(const std::string& host, int port);
		/// \return the remote host name/ip or "" if not set
		std::string getRemoteHost() const;

		/// \return the remote port or 0 if not set
		int getRemotePort() const;

		void addIntArg(int32_t arg);
		void addFloatArg(float arg);
		void addStringArg(String arg);

		int32_t getArgAsInt32(int index, bool typeConvert = false) const;
		float getArgAsFloat(int index, bool typeConvert = false) const;
		std::string getArgAsString(int index, bool typeConvert = false) const;
		int getNumArgs() const;

		gdOscArgType getArgType(int index) const;
		std::string getArgTypeName(int index) const;

		gdOscMessage& copy(const gdOscMessage& other);

	private:
		
		std::string address;  //< OSC address, must start with a /
							// std::vector<ofxOscArg*> args; //< current arguments

		std::string remoteHost;  //< host name/ip the message was sent from
		int remotePort;          //< port the message was sent from

		std::string typetag;

		std::vector<gdOscArg*> args;
		
	};

	class OscExc {};
	class OscExcInvalidArgumentType : public OscExc {};
	class OscExcOutOfBounds : public OscExc {};
	
};

#endif
