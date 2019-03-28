//
// WWW.hh
//
// This module embodies many of the standards by the World Wide Web Consortium (W3C),
// such as HTML and XML.
//
// But as it also includes other standards in use on the World Wide Web (e.g. HTTP),
// the module is simply called WWW.
//

#ifndef WWW_hh
#define WWW_hh

#include <map>
#include <set>

#include "../String/String.hh"

#include "../Socket/BSD.hh"

namespace WWW {

   class _WWW_;

   typedef std::set<String, NoCase> Set;

   typedef std::map<String, String, NoCase> Map;

   typedef std::map<String, Set, NoCase> MapSet;

   namespace HTTP {
   } // HTTP

   namespace HTML {
   } // HTML

   namespace XML {
   } // XML

} // W#WW

class WWW::_WWW_ : private _General_ {
}; // _WWW_

#endif // WWW_hh
