//
// Query.hh
//

#ifndef Query_hh
#define Query_hh

#include <map>
#include <list>

#include "../String/String.hh"

#include "BSD.hh"

namespace Query {

   class _Query_;

   class Interface;

   // A named BSD::Port
   class Service;

   typedef std::list<Interface> Interfaces;

   // Service names are unique
   typedef std::map<String, Service, NoCase> Services;

   // Service ports are not unique.
   // There may be a number of Services for each port
   typedef std::map<BSD::Port, Services> Ports;

} // Query

class Query::_Query_ : private _General_ {
}; // _Query_

#endif // Query_hh
