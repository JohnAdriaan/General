//
// Address.hh
//

#ifndef Address_hh
#define Address_hh

#ifdef __GNUC__

   #include <netinet/in.h>       // for sockaddr_*
   #include <netpacket/packet.h> // For sockaddr_ll

#endif // __GNUC__

#include "../String/String.hh"

#include "BSD.hh"

class BSD::Address : private _BSD_ {

public: // Static variables

   static const Address any4;

   static const Address any6;

   static const Address loopback4;

   static const Address loopback6;

public: // Methods

   Address();

   implicit Address(const sockaddr *addr);

   // Suitable for IPv4 and IPv6 addresses
   Address(const Address &address, BSD::Port port);

#ifdef __GNUC__
   // Suitable for Link addresses
   Address(word protocol, int index, const byte *addr=nullptr, byte addrLen=0);
#endif // __GNUC__

   inline BSD::Family Family() const;

   inline operator const sockaddr *() const;

   operator String() const;

   socklen_t Length() const;

   BSD::Port Port() const;

private: // Methods

   friend Raw;

   friend UDP;

   friend TCP;

   friend Listen;

   inline operator sockaddr *();

private: // Variables

   union {
      sockaddr         address;
      sockaddr_in      ipv4;
      sockaddr_in6     ipv6;
      sockaddr_storage storage;
#ifdef __GNUC__
      sockaddr_ll      link;
#endif // __GNUC__
   }; // union

}; // Address

inline BSD::Address::operator sockaddr *() {
   return &address;
} // Address::operator sockaddr *()

inline BSD::Address::operator const sockaddr *() const {
   return &address;
} // Address::operator const sockaddr *()

inline BSD::Family BSD::Address::Family() const {
   return address.sa_family;
} // Address:Family()

#endif // Address_hh
