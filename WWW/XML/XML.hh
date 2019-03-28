//
// XML.hh
//

#ifndef XML_hh
#define XML_hh

#include "../WWW.hh"

namespace WWW {

   namespace XML {

      enum NodeTypes {
         Element     = 1,
         Attribute   = 2,
         Text        = 3,
//       CDATA       = 4,
//       EntityRef   = 5,
//       Entity      = 6,
//       Instruction = 7,
         Comment     = 8,
         Document    = 9,
//       DocType     = 10,
//       DocFragment = 11,
//       Notation    = 12
      }; // NodeTypes

      // These characters are reserved
      extern const String quote;       // "
      extern const String lessThan;    // <
      extern const String ampersand;   // &
      extern const String apostrophe;  // '
      extern const String greaterThan; // >

      class _XML_;

      class Tag;

      class Element;

      class Document;

   } // XML

} // WWW

class WWW::XML::_XML_ : private _WWW_ {
}; // _XML_

#endif // XML_hh
