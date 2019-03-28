//
// Service.hh
//

#ifndef Service_hh
#define Service_hh

#include "../String/String.hh"
#include "Query.hh"

class Query::Service : private _Query_ {

public: // Static methods

   // Get map of Ports->Services
   static const Query::Ports &Ports();

   // Get map of Names->Service
   static const Query::Services &Services();

   // Get port from name.
   // Returns BSD::NoPort if not found
   static BSD::Port Find(const String &name);

public: // Methods

   Service();

   inline operator const String &() const;

   inline const String &Name() const;

   inline BSD::Port Port() const;

   inline bool TCP() const;

   inline bool UDP() const;

   // Datagram Delivery Protocol
   inline bool DDP() const;

   inline bool Alias() const;

private: // Methods

   Service(const String &name, BSD::Port port, bool alias);

private: // Variables

   String name;

   BSD::Port port;

   bool alias;

   // According to IANA, all ports are designated for both TCP and UDP. However...
   bool tcp;

   bool udp;

   bool ddp;// Datagram Delivery Protocol

private: // Static methods

   static void Add(Query::Services &services, const struct servent &entry);

}; // Service

inline Query::Service::operator const String &() const {
   return name;
} // Service::operator String()

inline const String &Query::Service::Name() const {
   return name;
} // Service::Name()

inline BSD::Port Query::Service::Port() const {
   return port;
} // Service::Port()

inline bool Query::Service::TCP() const {
   return tcp;
} // Service::TCP()

inline bool Query::Service::UDP() const {
   return udp;
} // Service::UDP()

inline bool Query::Service::DDP() const {
   return ddp;
} // Service::DDP()

inline bool Query::Service::Alias() const {
   return alias;
} // Service::Alias()

#endif // Service_hh
