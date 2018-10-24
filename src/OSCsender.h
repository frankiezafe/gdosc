#include <ip/UdpSocket.h>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include "Engine.hpp"
#include "Node.hpp"

#include "gdOscMessage.h"
#include "OscOutboundPacketStream.h"

#ifndef GDOSC_SENDER_H
#define GDOSC_SENDER_H

class OSCsender : public Node {
  GDCLASS(OSCsender, Node);

 public:
  OSCsender();
  ~OSCsender();

  bool init(String ip, int port);

  bool start();
  void stop();

  // message related

  // construction of the message
  void msg_address(const String& address);
  void msg_add_int(const int& i);
  void msg_add_real(const real_t& r);
  void msg_add_string(const String& s);
  void msg_add_v2(const Vector2& v);
  void msg_add_v3(const Vector3& v);
  void msg_add_quat(const Quat& q);
  void msg_add_transform(const Transform& t);

  // send the message
  void msg_send();

  /* cleanup of the message, automatically called on send
   * if autoclear is enabled
   */
  void msg_clear();

  // setters
  void set_ip(String ip);
  void set_port(int port);
  void set_buffersize(int buffersize);
  void set_autostart(bool autostart);
  void set_autoclear(bool autoclear);

  // getters
  _FORCE_INLINE_ const String& get_ip() const { return _ip; }
  _FORCE_INLINE_ const int& get_port() const { return _port; }
  _FORCE_INLINE_ const int& get_buffersize() const { return _buffersize; }
  _FORCE_INLINE_ const bool& is_autostart() const { return _autostart; }
  _FORCE_INLINE_ const bool& is_autoclear() const { return _autoclear; }
  _FORCE_INLINE_ const bool& is_ready() const { return _ready; }
  _FORCE_INLINE_ const bool& is_started() const { return _started; }

 protected:
  void _notification(int p_what);
  static void _bind_methods();

 private:
  String _ip;
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

#endif
