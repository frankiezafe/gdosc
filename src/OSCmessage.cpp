#include "OSCmessage.h"

using namespace godot;
using namespace gdosc;

OSCmessage::OSCmessage() : _port(0), _valid(false) {}

OSCmessage::OSCmessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
    : _port(0), _valid(false) {
  _address = String(m.AddressPattern());
  _typetag = String(m.TypeTags());
  char endpointHost[IpEndpointName::ADDRESS_STRING_LENGTH];
  remoteEndpoint.AddressAsString(endpointHost);
  _ip = String(endpointHost);
  _port = remoteEndpoint.port;

  try {
    for (::osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin(); arg != m.ArgumentsEnd();
         ++arg) {
      if (arg->IsInt32()) {
        _arguments.append(arg->AsInt32Unchecked());
      } else if (arg->IsFloat()) {
        _arguments.append(arg->AsFloatUnchecked());
      } else if (arg->IsString()) {
        _arguments.append(String(arg->AsStringUnchecked()));
      }
    }

  } catch (osc::Exception& e) {
    // any parsing errors such as unexpected argument types, or
    // missing arguments get thrown as exceptions.
    std::cout << "error while parsing message: " << m.AddressPattern() << ": " << e.what() << "\n";
  }

  _arg_num = _arguments.size();

  _valid = true;
}

OSCmessage::~OSCmessage() {}

void OSCmessage::copy(const OSCmessage& src) {
  _valid = src.is_valid();
  _ip = src.ip();
  _port = src.port();
  _address = src.address();
  _typetag = src.typetag();
  _arg_num = src.arg_num();
  _arguments = src.arguments();
}

void OSCmessage::_register_methods() {
	
	//register_property((char *)"base/name", &OSCmessage::_name, String("OSCmessage"));
	
	register_method((char *)"empty", &OSCmessage::empty);
	register_method((char *)"ip", &OSCmessage::ip);
	register_method((char *)"port", &OSCmessage::port);
	register_method((char *)"address", &OSCmessage::address);
	register_method((char *)"typetag", &OSCmessage::typetag);
	register_method((char *)"arg_num", &OSCmessage::arg_num);
	register_method((char *)"arg", &OSCmessage::arg);
	/*
	register_method((bool)"empty", &OSCmessage::empty);
	register_method((const String&)"ip", &OSCmessage::ip);
	register_method((const int&)"port", &OSCmessage::port);
	register_method((const String&)"address", &OSCmessage::address);
	register_method((const String&)"typetag", &OSCmessage::typetag);
	register_method((const int&)"arg_num", &OSCmessage::arg_num);
	register_method((const Variant&)"arg", &OSCmessage::arg);
	*/
}

/*
void OSCmessage::_bind_methods() {
  ClassDB::bind_method(D_METHOD("empty"), &OSCmessage::empty);
  ClassDB::bind_method(D_METHOD("ip"), &OSCmessage::ip);
  ClassDB::bind_method(D_METHOD("port"), &OSCmessage::port);
  ClassDB::bind_method(D_METHOD("address"), &OSCmessage::address);
  ClassDB::bind_method(D_METHOD("typetag"), &OSCmessage::typetag);
  ClassDB::bind_method(D_METHOD("arg_num"), &OSCmessage::arg_num);
  ClassDB::bind_method(D_METHOD("arg", "p_idx"), &OSCmessage::arg);
}
*/
