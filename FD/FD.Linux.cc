//
// FD.Linux.cc
//

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/sendfile.h>

#include "FD.hh"
#include "../String/String.hh"

template <typename T>
int FD<T>::IOCtl(int request, void* result) {
   if (!Valid()) {
      return -1;
   } // if
   int test = ::ioctl(fd, request, result);
   Test(test);
   return test;
} // FD::IOCtl(request, result)

template <typename T>
bool FD<T>::SendFile(FD& source, Size size) {
   if (!Valid()) {
      return false;
   } // if
   if (!source.Valid()) {
      return false;
   } // if
   for (ever) {
      ssize_t wrote = ::sendfile(fd, source.fd, nullptr, size); // From current
      if (!Test(wrote)) { // Error?
         return false;
      } // if
      if (wrote == 0) {  // End of file?
         break;
      } // if
      size -= wrote;
      if (size == 0) {     // All she wrote?
         break;
      } // if
   } // for
   return true;
} // FD::SendFile(FD, size)
