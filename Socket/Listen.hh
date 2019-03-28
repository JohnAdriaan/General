//
// Listen.hh
//

#ifndef Listen_hh
#define Listen_hh

#include "Socket.hh"

class BSD::Listen : public Socket {

protected: // Methods

   explicit Listen(BSD::Family family);

   Listen(const Address &address, Port port);

   bool Hear(const Address &address, Port port, unsigned queue=5);

   bool Accept();

   virtual ~Listen();

private: // Hooks

   hook void Heard(BSD::TCP &client, const Address &address) pure;

}; // Listen

#endif // Listen_hh
