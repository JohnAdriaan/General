//
// Service.cc
//

#include <netdb.h>
#include <string.h> // For strcmp()

#include "Service.hh"

using namespace Query;

const Query::Ports &Service::Ports() {
   static Query::Ports ports;

   if (!ports.empty()) {
      return ports;
   } // if

   ::setservent(true); // Stay open
   for (ever) {
      ::servent *entry = ::getservent();
      if (entry==nullptr) {
         break;
      } // if

      BSD::Port port = ntohs((BSD::Port)entry->s_port);
      const auto &p = ports.find(port);
      Query::Services &services = p==ports.end() ?
                                  ports[port] = Query::Services() : // Need new one
                                  p->second;                        // Use existing one
      Add(services, *entry);
   } // for
   ::endservent();
   return ports;
} // Service::Ports()

const Query::Services &Service::Services() {
   static Query::Services services;

   if (!services.empty()) {
      return services;
   } // if

   ::setservent(true); // Stay open
   for (ever) {
      ::servent *entry = ::getservent();
      if (entry==nullptr) {
         break;
      } // if

      Add(services, *entry);
   } // for
   ::endservent();
   return services;
} // Service::Services()

BSD::Port Service::Find(const String &name) {
   BSD::Port port = (BSD::Port)ToNumber(name); // Already a number?
   if (port!=BSD::NoPort) {
      return port;                             // Yes, so return it!
   } // if
   const Query::Services &services = Service::Services();
   const auto &s = services.find(name);
   return s!=services.end() ?
          s->second.Port() :
          BSD::NoPort;
} // Service::Find(name)

void Service::Add(Query::Services &services, const ::servent &entry) {
   bool tcp = ::strcmp(entry.s_proto, "tcp")==0;
   bool udp = ::strcmp(entry.s_proto, "udp")==0;
   bool ddp = ::strcmp(entry.s_proto, "ddp")==0;
   if (!tcp && !udp && !ddp) {
      return; // Unknown protocol
   } // if

   BSD::Port port = ntohs((BSD::Port)entry.s_port);

#define isAlias (alias!=&entry.s_name) // Helper calculation
   for (const char * const *alias = &entry.s_name;
        alias!=nullptr && *alias!=nullptr;
        (isAlias ? ++alias : (alias=entry.s_aliases))) {
      String name = *alias;
      const auto &s = services.find(name);
      Service &service = s==services.end() ?
                         services[name] = Service(name,port,isAlias) : // Need new one
                         s->second;                                    // Use existing one
      if (service.port!=port) {
         continue; // Attempt to use already-defined name!
      } // if
      service.tcp = service.tcp || tcp;
      service.udp = service.udp || udp;
      service.ddp = service.ddp || ddp;
   } // for
} // Service::Add(Services, entry)
