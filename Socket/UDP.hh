//
// UDP.hh
//

#ifndef UDP_hh
#define UDP_hh

#include "Socket.hh"

class BSD::UDP : public Socket {

public: // Methods

   explicit UDP(BSD::Family family, Protocols protocol=Protocols::Default);

   bool Connect(const Address &to);

   bool RecvFrom(void *data, Size size, Size &read, Address &from, int flags=0);

   bool SendTo(const void *data, Size size, Size &wrote, const Address &to, int flags=0);

protected: // Methods

   explicit UDP(UDP &UDP) = default;

}; // UDP

#endif // UDP_hh
