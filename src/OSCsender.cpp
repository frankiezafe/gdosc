#include "OSCsender.h"

OSCsender::OSCsender()
    : _ip("127.0.0.1"),
      _port(0),
      _buffersize(1024),
      _autostart(true),
      _autoclear(true),
      _ready(false),
      _started(false) {}

OSCsender::~OSCsender() { stop(); }

bool OSCsender::init(String ip, int port) {
  stop();

  _ip = ip;
  _port = port;

  std::wstring ws = _ip.c_str();
  std::string ipstring(ws.begin(), ws.end());

  if (_ip.empty() || _port < 1) {
    std::cout << "OSCsender::init, invalid configuration: " << ipstring << ":" << _port
              << std::endl;
    return _ready;
  }
  _ready = true;
  start();

  return _ready;
}

bool OSCsender::start() {
  if (!_started) {
    if (!_ready) {
      std::cout << "OSCsender::start, failed to start" << std::endl;
    } else {
      std::wstring ws = _ip.c_str();
      std::string ipstring(ws.begin(), ws.end());

      UdpTransmitSocket* socket = nullptr;

      try {
        _message_target = IpEndpointName(ipstring.c_str(), _port);
        socket = new UdpTransmitSocket(_message_target);
        _socket.reset(socket);
        std::cout << "OSCsender::start, started successfully: " << ipstring << ":" << _port
                  << std::endl;
        _started = true;

      } catch (std::exception& e) {
        std::cout << "failed creating sendSocket because: " << e.what() << std::endl;
        _socket.reset();
      }
    }
  }

  return _started;
}

void OSCsender::msg_address(const String& address) {
  if (!_started || address.empty()) return;
  msg.setAddress(utils::gdStringToString(address));
}

void OSCsender::msg_add_int(const int& i) {
  if (!_started) return;
  msg.addIntArg(i);
}

void OSCsender::msg_add_real(const real_t& r) {
  if (!_started) return;
  // this MUST be fine-tuned!
  msg.addFloatArg(r);
}

void OSCsender::msg_add_string(const String& s) {
  if (!_started) return;
  msg.addStringArg(utils::gdStringToString(s).c_str());
}

void OSCsender::msg_add_v2(const Vector2& v) {
  if (!_started) return;
  msg.addFloatArg(v[0]);
  msg.addFloatArg(v[1]);
}

void OSCsender::msg_add_v3(const Vector3& v) {
  if (!_started) return;
  msg.addFloatArg(v[0]);
  msg.addFloatArg(v[1]);
  msg.addFloatArg(v[2]);
}

void OSCsender::msg_add_quat(const Quat& q) {
  if (!_started) return;
  msg.addFloatArg(q.w);
  msg.addFloatArg(q.x);
  msg.addFloatArg(q.y);
  msg.addFloatArg(q.z);
}

void OSCsender::msg_add_transform(const Transform& t) {
  if (!_started) return;
  const Basis& b = t.basis;  // its a matrix 3x3!
  for (uint8_t i = 0; i < 3; ++i) {
    for (uint8_t j = 0; j < 3; ++j) {
      msg.addFloatArg(b.elements[i][j]);
    }
  }
  msg_add_v3(t.origin);
}

void OSCsender::msg_send() {
  if (!_started) return;

  char buffer[_buffersize];
  osc::OutboundPacketStream p(buffer, _buffersize);

  p << ::osc::BeginBundleImmediate;
  p << ::osc::BeginMessage(msg.getAddress().c_str());
  for (int i = 0; i < msg.getNumArgs(); ++i) {
    if (msg.getArgType(i) == TYPE_INT32) {
      p << msg.getArgAsInt32(i);
    } else if (msg.getArgType(i) == TYPE_FLOAT) {
      p << msg.getArgAsFloat(i);
    } else if (msg.getArgType(i) == TYPE_STRING) {
      p << msg.getArgAsString(i).c_str();
    } else {
      throw OscExcInvalidArgumentType();
    }
  }
  p << ::osc::EndMessage;
  p << ::osc::EndBundle;

  _socket->Send(p.Data(), p.Size());

  if (_autoclear) msg_clear();
}

void OSCsender::msg_clear() { msg.clear(); }

void OSCsender::stop() {
  if (_ready) {
    _socket.reset();
  }
  _started = false;
  _ready = false;
}

void OSCsender::_notification(int p_what) {
  switch (p_what) {
    case MainLoop::NOTIFICATION_WM_QUIT_REQUEST: {
      std::cout << "OSCsender::_notification, stopping emission" << std::endl;
      stop();
    } break;
    case NOTIFICATION_READY: {
      if (_autostart) {
        std::cout << "OSCsender::_notification, starting emission" << std::endl;
        start();
      }
    } break;
  }
  // std::cout << p_what << std::endl;
}

void OSCsender::set_ip(String ip) { init(ip, _port); }

void OSCsender::set_port(int port) {
  init(_ip, port);
  std::cout << "Setting port: " << port << std::endl;
}

void OSCsender::set_buffersize(int buffersize) {
  if (buffersize > 0) {
    _buffersize = buffersize;
  }
}

void OSCsender::set_autostart(bool autostart) { _autostart = autostart; }

void OSCsender::set_autoclear(bool autoclear) { _autoclear = autoclear; }

void OSCsender::_bind_methods() {
  ClassDB::bind_method(D_METHOD("init", "ip", "port"), &OSCsender::init);
  ClassDB::bind_method(D_METHOD("start"), &OSCsender::start);
  ClassDB::bind_method(D_METHOD("stop"), &OSCsender::stop);

  ClassDB::bind_method(D_METHOD("msg_address", "address"), &OSCsender::msg_address);
  ClassDB::bind_method(D_METHOD("msg_add_int", "i"), &OSCsender::msg_add_int);
  ClassDB::bind_method(D_METHOD("msg_add_real", "r"), &OSCsender::msg_add_real);
  ClassDB::bind_method(D_METHOD("msg_add_string", "s"), &OSCsender::msg_add_string);
  ClassDB::bind_method(D_METHOD("msg_add_v2", "v"), &OSCsender::msg_add_v2);
  ClassDB::bind_method(D_METHOD("msg_add_v3", "v"), &OSCsender::msg_add_v3);
  ClassDB::bind_method(D_METHOD("msg_add_quat", "q"), &OSCsender::msg_add_quat);
  ClassDB::bind_method(D_METHOD("msg_add_transform", "t"), &OSCsender::msg_add_transform);
  ClassDB::bind_method(D_METHOD("msg_send"), &OSCsender::msg_send);
  ClassDB::bind_method(D_METHOD("msg_clear"), &OSCsender::msg_clear);

  ClassDB::bind_method(D_METHOD("set_ip", "ip"), &OSCsender::set_ip);
  ClassDB::bind_method(D_METHOD("set_port", "port"), &OSCsender::set_port);
  ClassDB::bind_method(D_METHOD("set_buffersize", "buffersize"), &OSCsender::set_buffersize);
  ClassDB::bind_method(D_METHOD("set_autostart", "autostart"), &OSCsender::set_autostart);
  ClassDB::bind_method(D_METHOD("set_autoclear", "autoclear"), &OSCsender::set_autoclear);

  ClassDB::bind_method(D_METHOD("get_ip"), &OSCsender::get_ip);
  ClassDB::bind_method(D_METHOD("get_port"), &OSCsender::get_port);
  ClassDB::bind_method(D_METHOD("get_buffersize"), &OSCsender::get_buffersize);
  ClassDB::bind_method(D_METHOD("is_autostart"), &OSCsender::is_autostart);
  ClassDB::bind_method(D_METHOD("is_autoclear"), &OSCsender::is_autoclear);
  ClassDB::bind_method(D_METHOD("is_ready"), &OSCsender::is_ready);
  ClassDB::bind_method(D_METHOD("is_started"), &OSCsender::is_started);

  ADD_GROUP("Network", "");
  ADD_PROPERTY(PropertyInfo(Variant::STRING, "ip", PROPERTY_HINT_LENGTH, "7"), "set_ip", "get_ip");
  ADD_PROPERTY(
      PropertyInfo(Variant::INT, "port", PROPERTY_HINT_RANGE, "1,99999,1"), "set_port", "get_port");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "buffersize", PROPERTY_HINT_RANGE, "1,327680,1"),
               "set_buffersize",
               "get_buffersize");
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "autostart"), "set_autostart", "is_autostart");
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "autoclear"), "set_autoclear", "is_autoclear");
}
