//
// Listen.cc
//

#include "TCP.hh"
#include "Listen.hh"
#include "Address.hh"

using namespace BSD;

Listen::Listen(BSD::Family family) :
        Socket(family, Types::Stream) {
   if (!Valid()) {
      return;
   } // if
   SetOption(SOL_SOCKET, SO_REUSEADDR, true);
} // Listen::Listen(Family)

Listen::Listen(const Address &address, Port port) :
        Listen(address.Family()) {
   Hear(address, port);
} // Listen::Listen(Address,Port)

bool Listen::Hear(const Address &address, Port port, unsigned queue) {
   if (!Valid()) {
      return false;
   } // if
   Address local(address, port);
   if (!Test(::bind(fd, local, local.Length()))) {
      Close();
      return false;
   } // if
   if (!Test(::listen(fd, queue))) {
      Close();
      return false;
   } // if
   return true;
} // Listen::Hear(address, port, queue)

bool Listen::Accept() {
   if (!Valid()) {
      return false;
   } // if

   Address address;
   socklen_t length = address.Length();
   FD::Type heard = ::accept(fd, address, &length);
   if (!Test(heard)) {
      return false;
   } // if

   BSD::TCP tcp(heard);
   Heard(tcp, address);
   return true;
} // Listen::Accept()

Listen::~Listen() {
   Close();
} // Listen::~Listen()
