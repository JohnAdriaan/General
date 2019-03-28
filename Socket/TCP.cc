//
// TCP.cc
//

#include "Address.hh"
#include "TCP.hh"

using namespace BSD;

TCP::TCP(FD::Type client) :
     Socket(client) {
} // TCP::TCP(client)

TCP::TCP(BSD::Family family, Protocols protocol/*=Default*/) :
     Socket(family,Types::Stream,protocol) {
} // TCP::TCP(family, protocol)

bool TCP::Connect(const Address &to) {
   return Test(::connect(fd,to,to.Length()));
} // TCP::Connect(Address)
