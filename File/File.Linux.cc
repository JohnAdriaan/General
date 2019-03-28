//
// File.cc
//

#include <wordexp.h>

#include "File.hh"

String File::Expand(const String &name) {
   wordexp_t expand;
   ::wordexp(name.c_str(), &expand, 0);
   String result = expand.we_wordv[0];
   ::wordfree(&expand);
   return result;
} // File::Expand(name)
