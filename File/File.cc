//
// File.cc
//

#include <fcntl.h>

#ifdef _MSC_VER

   #define _CRT_SECURE_NO_WARNINGS
   #include <io.h>
   #undef  _CRT_SECURE_NO_WARNINGS

   typedef int mode_t;

#endif // _MSC_VER

#ifdef __GNUC__

   #include <unistd.h>

   // ISO versions of these names
   #define _open  open
   #define _lseek lseek

#endif // __GNUC__

#include "File.hh"

static mode_t Mode(File::Accesses access,
                   File::Creates create) {
   mode_t mode = 0;
   switch (access) {
   case File::ReadOnly :
      mode |= O_RDONLY;
      break;
   case File::WriteOnly :
      mode |= O_WRONLY;
      break;
   case File::ReadWrite :
      mode |= O_RDWR;
      break;
   } // switch
   switch (create) {
   case File::Exists :
//    mode |= 0;
      break;
   case File::Create :
      mode |= O_CREAT;
      break;
   case File::Exclusive :
      mode |= O_CREAT|O_EXCL;
      break;
   case File::Truncate :
      mode |= O_CREAT|O_TRUNC;
      break;
   } // switch
   return mode;
} // Mode(access, create)

File::File(const char *path, Accesses access, Creates create) :
      FD(::_open(path,Mode(access,create))) {
   Test(fd);
} // File::File(path, access, create)

::Size File::Size() const {
   if (!Valid()) {
      return 0;
   } // if
   off_t old = ::_lseek(fd, 0, SEEK_CUR);
   off_t pos = ::_lseek(fd, 0, SEEK_END);
   ::_lseek(fd, old, SEEK_SET);
   return pos;
} // File::Size()
