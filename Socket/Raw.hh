//
// Raw.hh
//

#ifndef Raw_hh
#define Raw_hh

#include <net/if.h>

#include "Socket.hh"

class BSD::Raw : public BSD::Socket {

public: // Methods

   // To set promiscuous mode, user needs to have CAP_NET_ADMIN capability
   Raw(const String &interface, Protocols protocol, bool promiscuous=false);

   bool SetFlag(short flag);

   bool ResetFlag(short flag);

   bool RecvFrom(void *data, Size size, Size &read, Address &from, int flags=0);

   void Close();

protected: // Variables

   ::ifreq req;

   short flags;

   // Index of passed-in interface
   int index;

}; // Raw

#endif // Raw_hh
