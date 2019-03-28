//
// UDP.cc
//

#include "Address.hh"
#include "UDP.hh"

using namespace BSD;

UDP::UDP(BSD::Family family, Protocols protocol/*=Default*/) :
     Socket(family,Types::Stream,protocol) {
} // UDP::UDP(family, protocol)

bool UDP::Connect(const Address &to) {
   return Test(::connect(fd,to,to.Length()));
} // UDP::Connect(Address)

bool UDP::RecvFrom(void *data, Size size, Size &read, Address &from, int flags) {
   if (!Valid()) {
      return false;
   } // if
   socklen_t length = from.Length();
   read = (Size)::recvfrom(fd, static_cast<char *>(data), static_cast<int>(size), flags, from, &length );
   return Test(read);
} // UDP::RecvFrom(data, size, read, from, flags)

bool UDP::SendTo(const void *data, Size size, Size &wrote, const Address &to, int flags) {
   if (!Valid()) {
      return false;
   } // if
   wrote = (Size)::sendto(fd, static_cast<const char *>(data), static_cast<int>(size), flags, to, to.Length() );
   return Test(wrote);
} // UDP::SendTo(data, size, wrote, to, flags)
