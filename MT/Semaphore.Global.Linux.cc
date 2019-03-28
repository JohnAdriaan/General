//
// Semaphore.Global.Linux.cc
//

#include <fcntl.h>    // For O_*
#include <sys/stat.h> // For S_*

#include "Semaphore.Global.hh"

//static const int share = S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH;
static const int share = S_IREAD|S_IWRITE;

using namespace MT;

Semaphore::Global::Global(const char *name,
                          Creates create/*=Exists*/,
                          unsigned start/*=0*/) :
           Semaphore(SEM_FAILED),
           name(name),
           unlink(true) {
   int oflags = O_RDWR;
   switch (create) {
   case Exists :
   // oflags |= 0;
      break;
   case Create :
      oflags |= O_CREAT;
      break;
   case Exclusive :
      oflags |= O_CREAT|O_EXCL;
      break;
   } // switch
   semaphore = ::sem_open(name, oflags, share, start);
} // Global::Global(name,create,start)

Semaphore::Global::Global(const char *name, bool &already) :
           Global(name, Exclusive) { // Attempt to create
   already = false;   // Assume didn't already exist
   if (Valid()) {     // Did create work?
      return;         // Yes - assumption correct
   } // if
   semaphore = ::sem_open(name, O_RDWR); // Attempt to open existing
   if (Valid()) {     // Did open work?
      already = true; // Yes - so already existed
      unlink = false; // Don't unlink - let creator do so
      return;
   } // if
// semaphore = ::sem_open(name, O_RDWR|O_CREAT, share, 0); // Something's odd...
} // Glboal::Global(name,already)

void Semaphore::Global::Close() {
   sem_t *temp = semaphore;
   semaphore = SEM_FAILED;
   if (temp==SEM_FAILED) {
      return;
   } // if
   ::sem_close(temp);
} // Global::Close()

void Semaphore::Global::Unlink() {
   if (name==nullptr) {
      return;
   } // if
   ::sem_unlink(name);
} // Global::Unlink()

void Semaphore::Global::SetUnlink(bool doUnlink) {
   unlink = doUnlink;
} // Global::SetUnlink(doUnlink)

Semaphore::Global::~Global() {
   Close();
   if (unlink) {
      Unlink();
   } // if
} // Global::~Global()
