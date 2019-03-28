//
// FD.cc
//

#include <errno.h>

#ifdef _MSC_VER

   #include <io.h>

#endif // _MSC_VER

#ifdef __GNUC__

   #include <unistd.h>

   // ISO versions of these names
   #define _open  open
   #define _read  read
   #define _write write
   #define _close close

#endif // __GNUC__

#include "FD.hh"
#include "../String/String.hh"

template <typename T>
FD<T>::FD(Type fd) :
       fd(fd),
       err(0) {
} // FD::FD(fd)

template <typename T>
FD<T>::FD(FD &fd) :
       fd(fd.fd),
       err(0) {
   fd.fd = Invalid;
} // FD::FD(FD)

#ifndef NDEBUG
#include <iostream>
template <typename T>
bool FD<T>::Error(int result, const char *call) {
   if (result!=-1) {
      return true;
   } // if
   err = errno;
   std::cerr << "Error! " << call << ": " << err << std::endl;
   return false;
} // FD::Error(result,call)
#endif // !NDEBUG

template <typename T>
bool FD<T>::Read(void* buffer, Size size, Size& read) {
   if (!Valid()) {
      return false;
   } // if
   read = ::_read(fd, buffer, static_cast<unsigned>(size));
   return Test(read);
} // FD::Read(buffer, size, read)

template <typename T>
bool FD<T>::Write(const void* buffer, Size size, Size& wrote) {
   if (!Valid()) {
      return false;
   } // if
   wrote = ::_write(fd, buffer, static_cast<unsigned>(size));
   return Test(wrote);
} // FD::Write(buffer, size, wrote)

template <typename T>
bool FD<T>::Write(const String &string) {
   return Write(string.c_str(), string.length());
} // FD::Write(string)

template <typename T>
bool FD<T>::Write(const void *buffer, Size size) {
   if (!Valid()) {
      return false;
   } // if
   Size wrote;
   while (size>0) {
      if (!Write(buffer, size, wrote)) {
         return false;
      } // if
      reinterpret_cast<const byte *&>(buffer) += wrote; // Avoid arithmetic warning
      size -= wrote;
   } // while
   return true;
} // FD::Write(buffer, size)

template <typename T>
void FD<T>::Close() {
   Type old = fd;
   if (!Valid()) {
      return;
   } // if
   fd = Invalid;
   Test(::_close(old));
} // FD::Close()

template <typename T>
FD<T>::~FD() {
   Close();
} // FD::~FD()
