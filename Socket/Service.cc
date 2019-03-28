//
// Service.cc
//

#include "Service.hh"

using namespace Query;

Service::Service() :
         Service(String(), BSD::NoPort, false) {
} // Service::Service()

Service::Service(const String &name, BSD::Port port, bool alias) :
         name(name),
         port(port),
         alias(alias),
         tcp(false),
         udp(false),
         ddp(false) {
} // Service::Service(name, port, alias)
