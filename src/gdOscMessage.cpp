#include "gdOscMessage.h"

using namespace godot;

gdOscMessage::gdOscMessage() : remoteHost(""), remotePort(0) {}

gdOscMessage::~gdOscMessage() { clear(); }

void gdOscMessage::setAddress(const std::string& address) { this->address = address; }

void gdOscMessage::setTypetag(const std::string& typetag) { this->typetag = typetag; }

//--------------------------------------------------------------
std::string gdOscMessage::getAddress() const { return address; }

//--------------------------------------------------------------
std::string gdOscMessage::getRemoteIp() const { return remoteHost; }

//--------------------------------------------------------------
std::string gdOscMessage::getTypetag() const { return typetag; }

//--------------------------------------------------------------
std::string gdOscMessage::getRemoteHost() const { return remoteHost; }

//--------------------------------------------------------------
int gdOscMessage::getRemotePort() const { return remotePort; }

void gdOscMessage::setRemoteEndpoint(const std::string& host, int port) {
  remoteHost = host;
  remotePort = port;
}

void gdOscMessage::addIntArg(int32_t arg) { args.push_back(new gdOscArgInt32(arg)); }

void gdOscMessage::addFloatArg(float arg) { args.push_back(new gdOscArgFloat(arg)); }

void gdOscMessage::addStringArg(String arg) {
  std::string s(utils::gdStringToString(arg));
  args.push_back(new gdOscArgString(s));
}

int32_t gdOscMessage::getArgAsInt32(int index, bool typeConvert) const {
  if (getArgType(index) != TYPE_INT32) {
    if (typeConvert && (getArgType(index) == TYPE_FLOAT))
      return (int32_t)((gdOscArgFloat*)args[index])->get();
    else
      throw OscExcInvalidArgumentType();
  } else
    return ((gdOscArgInt32*)args[index])->get();
}

float gdOscMessage::getArgAsFloat(int index, bool typeConvert) const {
  if (getArgType(index) != TYPE_FLOAT) {
    if (typeConvert && (getArgType(index) == TYPE_INT32))
      return (float)((gdOscArgInt32*)args[index])->get();
    else
      throw OscExcInvalidArgumentType();
  } else
    return ((gdOscArgFloat*)args[index])->get();
}

std::string gdOscMessage::getArgAsString(int index, bool typeConvert) const {
  if (getArgType(index) != TYPE_STRING) {
    if (typeConvert && (getArgType(index) == TYPE_FLOAT)) {
      char buf[1024];
      sprintf(buf, "%f", ((gdOscArgFloat*)args[index])->get());
      return std::string(buf);
    } else if (typeConvert && (getArgType(index) == TYPE_INT32)) {
      char buf[1024];
      sprintf(buf, "%i", ((gdOscArgInt32*)args[index])->get());
      return std::string(buf);
    } else
      throw OscExcInvalidArgumentType();
  } else
    return ((gdOscArgString*)args[index])->get();
}

int gdOscMessage::getNumArgs() const { return args.size(); }

gdOscArgType gdOscMessage::getArgType(int index) const {
  if (index >= (int)args.size()) {
    throw OscExcOutOfBounds();
  } else {
    return args[index]->getType();
  }
}

std::string gdOscMessage::getArgTypeName(int index) const {
  if (index >= (int)args.size()) {
    throw OscExcOutOfBounds();
  } else {
    return args[index]->getTypeName();
  }
}

gdOscMessage& gdOscMessage::copy(const gdOscMessage& other) {
  address = other.address;

  remoteHost = other.remoteHost;
  remotePort = other.remotePort;

  for (int i = 0; i < (int)other.args.size(); ++i) {
    gdOscArgType argType = other.getArgType(i);
    if (argType == TYPE_INT32)
      args.push_back(new gdOscArgInt32(other.getArgAsInt32(i)));
    else if (argType == TYPE_FLOAT)
      args.push_back(new gdOscArgFloat(other.getArgAsFloat(i)));
    else if (argType == TYPE_STRING)
      args.push_back(new gdOscArgString(other.getArgAsString(i)));
    else {
      throw OscExcInvalidArgumentType();
    }
  }

  return *this;
}
void gdOscMessage::clear() {
  address = "";
  remoteHost = "";
  remotePort = 0;
  // for(unsigned int i = 0; i < args.size(); ++i){
  // 	delete args[i];
  // }
  args.clear();
}
