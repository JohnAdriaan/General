//
// Address.cc
//

#ifdef __GNUC__

   #include <arpa/inet.h>      // For inet_ntop
   //#include <linux/if_arp.h>   // For ARP hardware type
   #include <linux/if_ether.h> // For link protocols     // TODO

#endif // __GNUC__

#include "Address.hh"

using namespace BSD;

static const sockaddr_in any4 = { AF_INET, 0, INADDR_ANY, { 0 } };

#ifdef __GNUC__

   static const sockaddr_in loop4 = { AF_INET, 0, INADDR_LOOPBACK, { 0 } };

#endif // __GNUC__

#ifdef _MSC_VER

   static const sockaddr_in loop4 = { AF_INET, 0,
                                   { { (INADDR_LOOPBACK >> 24) & 0xFF,
                                       (INADDR_LOOPBACK >> 16) & 0xFF,
                                       (INADDR_LOOPBACK >>  8) & 0xFF,
                                       (INADDR_LOOPBACK >>  0) & 0xFF} },
                                   { 0 } };

#endif // _MSC_VER

static const sockaddr_in6 any6 =  { AF_INET6, 0, 0, IN6ADDR_ANY_INIT, 0 };

static const sockaddr_in6 loop6 = { AF_INET6, 0, 0, IN6ADDR_LOOPBACK_INIT, 0 };

const Address Address::any4 = (sockaddr *)&::any4;

const Address Address::any6 = (sockaddr *)&::any6;

const Address Address::loopback4 = (sockaddr *)&::loop4;

const Address Address::loopback6 = (sockaddr *)&::loop6;

Address::Address() :
         storage( { 0, { 0 }, 0 } ) {
} // Address::Address()

Address::Address(const sockaddr *addr) :
         address( { addr->sa_family, { 0 } }) {
   switch (Family()) {
#ifdef __GNUC__
   case AF_PACKET :
      link = *(const sockaddr_ll *)addr;
      break;
#endif // __GNUC__
   case AF_INET :
      ipv4 = *(const sockaddr_in *)addr;
      break;
   case AF_INET6 :
      ipv6 = *(const sockaddr_in6 *)addr;
      break;
   default :
      address = *addr;
      break;
   } // switch
} // Address::Address(sockaddr*)

Address::Address(const Address &rhs, BSD::Port port) :
         storage(rhs.storage) {
   switch (Family()) {
   case AF_INET :
      ipv4.sin_port = htons(port);
      break;
   case AF_INET6 :
      ipv6.sin6_port = htons(port);
      break;
   default :
      break;
   } // switch
} // Address::Address(Address, Port)

Address::operator String() const {
   const void *data;

   switch (Family()) {
   case AF_INET :
      data = &ipv4.sin_addr;
      break;
   case AF_INET6 :
      data = &ipv6.sin6_addr;
      break;
   default :
      data = &address.sa_data;
      break;
   } // switch

   char str[INET6_ADDRSTRLEN];
   ::inet_ntop(address.sa_family, data, str, sizeof str);
   return str;
} // Address::operator String()

socklen_t Address::Length() const {
   switch (Family()) {
   case 0 :
      return sizeof storage;
#ifdef __GNUC__
   case AF_PACKET :
      return sizeof link;
#endif // __GNUC__
   case AF_INET :
      return sizeof ipv4;
   case AF_INET6 :
      return sizeof ipv6;
   default :
      return sizeof address;
   } // switch
} // Address::Length()

BSD::Port Address::Port() const {
   switch (Family()) {
   case AF_INET :
      return ntohs(ipv4.sin_port);
   case AF_INET6 :
      return ntohs(ipv6.sin6_port);
   default :
      return 0;
   } // switch
} // Address::Port()
