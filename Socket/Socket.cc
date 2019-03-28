//
// Socket.cc
//

#ifdef __GNUC__

   #include <netinet/in.h>       // for IPPROTO_*
   #include <linux/if_ether.h>   // for ETH_P_ALL

#endif // __GNUC__

#include "Socket.hh"

using namespace BSD;

static short GetProtocol(Socket::Protocols protocol) {
   switch (protocol) {
   case Socket::Protocols::Default :
      return 0;
   case Socket::Protocols::ICMP :
      return IPPROTO_ICMP;
   case Socket::Protocols::UDP :
      return IPPROTO_UDP;
   case Socket::Protocols::TCP :
      return IPPROTO_TCP;
   case Socket::Protocols::SCTP:
      return IPPROTO_SCTP;
#ifdef __GNUC__
   case Socket::Protocols::DCCP :
      return IPPROTO_DCCP;
   case Socket::Protocols::UDPLite :
      return IPPROTO_UDPLITE;
   case Socket::Protocols::All :
      return htons(ETH_P_ALL); // Different from IPPROTO_RAW
#endif // __GNUC__
   } // switch
   return protocol;
} // GetProtocol(protocol)

Socket::Socket(FD::Type fd) :
        FD(fd) {
} // Socket::Socket(fd)

Socket::Socket(Families family, Types type, Protocols protocol/*=Default*/) :
        FD(::socket(family,type,GetProtocol(protocol))) {
   Test(fd);
} // Socket::Socket(family, type, protocol)

Socket::Socket(BSD::Family family, Types type, Protocols protocol/*=Default*/) :
        FD(::socket(family,type,GetProtocol(protocol))) {
   Test(fd);
} // Socket::Socket(family, type, protocol)

bool Socket::Recv(void *data, Size size, Size &read, int flags) {
   if (!Valid()) {
      return false;
   } // if
   read = (Size)::recv(fd, static_cast<char *>(data), static_cast<int>(size), flags);
   return Test(read);
} // Socket::Recv(data, size, read, flags)

bool Socket::Send(const void *data, Size size, Size &wrote, int flags) {
   if (!Valid()) {
      return false;
   } // if
   wrote = (Size)::send(fd, static_cast<const char *>(data), static_cast<int>(size), flags);
   return Test(wrote);
} // Socket::Send(data, size, wrote, flags)

bool Socket::SetOption(int level, int option, bool on) {
   int value = on ? 1 : 0;
   return SetOption(level, option, &value, sizeof value);
} // Socket::SetOption(level, option, on)

bool Socket::SetOption(int level, int option, void *data, socklen_t size) {
   return Test(::setsockopt(fd, level, option, static_cast<const char *>(data), size));
} // Socket::SetOption(option, data, size)
