//
// Socket.hh

#ifndef Socket_hh
#define Socket_hh

#ifdef __GNUC__

   #include <sys/socket.h>

#endif // __GNUC__

#include "../FD/FD.hh"

#include "BSD.hh"

class BSD::Socket : public FD<SOCKETTYPE> {

public: // Enums

   enum Families {
      Unix   = AF_UNIX,
      IPv4   = AF_INET,
      IPv6   = AF_INET6,
#ifdef __GNUC__
      Packet = AF_PACKET
#endif // __GNUC__
   }; // Families

   enum Types {
      Raw       = SOCK_RAW,
      Datagram  = SOCK_DGRAM,
      Stream    = SOCK_STREAM,
      SeqPacket = SOCK_SEQPACKET
   }; // Types

   enum Protocols : short {
      Default = 0,
      ICMP,
      UDP,
      TCP,
      DCCP,
      SCTP,
      UDPLite,
      All
   }; // Protocols

public: // Methods

   bool Recv(void *data, Size size, Size &read, int flags=0);

   bool Send(const void *data, Size size, Size &wrote, int flags=0);

protected: // Methods

   explicit Socket(FD::Type fd);

   Socket(Families family, Types type, Protocols protocol=Protocols::Default);

   Socket(BSD::Family family, Types type, Protocols protocol=Protocols::Default);

   explicit Socket(Socket &socket) = default;

   bool SetOption(int level, int option, bool on);

   bool SetOption(int level, int option, void *data, socklen_t size);

}; // Socket

#endif // Socket_hh
