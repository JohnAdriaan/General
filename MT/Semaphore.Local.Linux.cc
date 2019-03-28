//
// Semaphore.Local.Linux.cc
//

#include "Semaphore.Local.hh"

using namespace MT;

Semaphore::Local::Local(unsigned start/*=0*/) :
                  Semaphore(&sem),
                  sem() {
   ::sem_init(semaphore, 0, start);
} // Local::Local(start)

void Semaphore::Local::Close() {
   sem_t *temp = semaphore;
   semaphore = SEM_FAILED;
   if (temp==SEM_FAILED) {
      return;
   } // if
   ::sem_destroy(temp);
} // Local::Close()

Semaphore::Local::~Local() {
   Close();
} // Local::~Local()
