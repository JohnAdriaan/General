//
// Raw.Linux.cc
//

#include <sys/ioctl.h>

#include "Address.hh"
#include "Raw.hh"

using namespace BSD;

Raw::Raw(const String &interface, Protocols protocol, bool promiscuous) :
     Socket(Families::Packet, Types::Raw, protocol),
     req(),
     flags(-1),
     index(-1) {
   if (!Valid()) {
      return;
   } // if

   if (!SetOption(SOL_SOCKET, SO_BROADCAST, true)) { // May not be necessary
      Close();
      return;
   } // if

   interface.copy(req.ifr_name, sizeof req.ifr_name-1); // Already NUL terminated above
   if (Test(IOCtl(SIOCGIFFLAGS, &req))) {
      flags = req.ifr_flags;
   } // if

   if (promiscuous) {
      SetFlag(IFF_PROMISC);
   } // if

   if (!Test(IOCtl(SIOCGIFINDEX, &req))) {
      Close();
      return;
   } // if
   index = req.ifr_ifindex;

   BSD::Address address(protocol, index);
   if (!Test(::bind(fd, address, address.Length()))) {
      Close();
      return;
   } // if
} // Raw::Raw(interface, protocol, promiscuous)

bool Raw::RecvFrom(void *data, Size size, Size &read, Address &from, int flags) {
   if (!Valid()) {
      return false;
   } // if
   socklen_t length = from.Length();
   read = (Size)::recvfrom(fd, data, size, flags, from, &length );
   return Test(read);
} // Raw::RecvFrom(data, size, read, from, flags)

bool Raw::SetFlag(short flag) {
   if (!Test(IOCtl(SIOCGIFFLAGS, &req))) {
      return false;
   } // if
   req.ifr_flags |= flag;
   return Test(IOCtl(SIOCSIFFLAGS, &req));
} // Raw::SetFlag(flag)

bool Raw::ResetFlag(short flag) {
   if (!Test(IOCtl(SIOCGIFFLAGS, &req))) {
      return false;
   } // if
   req.ifr_flags &= (short)~flag;
   return Test(IOCtl(SIOCSIFFLAGS, &req));
} // Raw::ResetFlag(flag)

void Raw::Close() {
   if (!Valid()) {
      return;
   } // if
   if (flags!=-1) {
      req.ifr_flags = flags;
      Test(IOCtl(SIOCSIFFLAGS, &req));
   } // if
   Socket::Close();
} // Raw::Close()
