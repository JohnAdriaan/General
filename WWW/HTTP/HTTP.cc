//
// HTTP.cc
//

#include "HTTP.hh"

using namespace WWW;

const String HTTP::EOL           = "\r\n";
const String HTTP::Close         = "close";
const String HTTP::Allow         = "Allow";
const String HTTP::MaxAge        = "max-age=";
const String HTTP::Location      = "Location";
const String HTTP::KeepAlive     = "keep-alive";
const String HTTP::Connection    = "Connection";
const String HTTP::CacheControl  = "Cache-Control";
const String HTTP::ContentLength = "Content-Length";

static const String HTTP10 = "HTTP/1.0";
static const String HTTP11 = "HTTP/1.1";

String HTTP::Version(HTTP::Versions version) {
   switch (version) {
   case HTTP::HTTP10 :
      return ::HTTP10;
   case HTTP::HTTP11:
      return ::HTTP11;
   case HTTP::Versions::Unknown :
   default :
      return "";
   } // switch
} // Version(version)

HTTP::Versions HTTP::Version(const String &version) {
   if (NoCase::Equal(version, ::HTTP11)) {
      return HTTP::HTTP11;
   } // if
   if (NoCase::Equal(version, ::HTTP10)) {
      return HTTP::HTTP10;
   } // if
   if (version=="") {
      return HTTP::HTTP10;
   } // if
   return HTTP::Versions::Unknown;
} // Version(version)
