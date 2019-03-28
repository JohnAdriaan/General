//
// TCP.hh
//

#ifndef TCP_hh
#define TCP_hh

#include "Socket.hh"

class BSD::TCP : public Socket {

public: // Methods

   explicit TCP(BSD::Family family, Protocols protocol=Protocols::Default);

   bool Connect(const Address &to);

protected: // Methods

   explicit TCP(TCP &tcp) = default;

private: // Listen methods

   friend Listen;

   explicit TCP(FD::Type client);

}; // TCP

#endif // TCP_hh
