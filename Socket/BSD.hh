//
// BSD.hh
//

#ifndef BSD_hh
#define BSD_hh

#ifdef _MSC_VER

   #include "../Windows/Windows.hh"
   #include <winsock2.h>
   #include <WS2tcpip.h>

   #define SOCKETTYPE SOCKET

#endif // _MSC_VER

#ifdef __GNUC__

   #define SOCKETTYPE int

#endif // __GNUC__

#include "../General.hh"

namespace BSD {

   typedef word Port;

   typedef word Family;

   class _BSD_;

   class Address;

   class Socket;

   class Listen;

   class Raw;

   class UDP;

   class TCP;

   static const Port NoPort = 0;
   static const Port ReservedPorts = 1023;
   static const Port MaxPort = 65535;

} // BSD

class BSD::_BSD_ : private _General_ {
}; // _BSD_

#endif // BSD_hh
