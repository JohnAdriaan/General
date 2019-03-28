//
// Interface.hh
//

#ifndef Interface_hh
#define Interface_hh

#include "Address.hh"

#include "Query.hh"

class Query::Interface : private _Query_ {

public: // Enums

   enum Protocols {
      NoProtocol,
      IPv4,
      IPv6,
      IPv46,
      AnyProtocol
   }; // Protocols

   enum States {
      NoState,
      Loopback,
      Up,
      Down,
      UpDown
   }; // States

public: // Static methods

   static Interfaces List(Protocols protocol, States state);

public: // Methods

   inline operator const String &() const;

public: // Variables

   const String name;

   const BSD::Address address;

   const Protocols protocol;

   const States state;

private: // Methods

   Interface(const char *name,
             const sockaddr *addr,
             Protocols protocol,
             States state);

}; // Interface

inline Query::Interface::operator const String &() const {
   return name;
} // Interface::operator String()

#endif // Interface_hh
