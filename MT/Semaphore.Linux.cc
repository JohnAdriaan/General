//
// Semaphore.Linux.cc
//

#include "Semaphore.hh"

using namespace MT;

Semaphore::Semaphore(SEMAPHORETYPE semaphore) :
           semaphore(semaphore) {
} // Semaphore::Semaphore(start)

bool MT::Semaphore::Valid() const {
   return semaphore != SEM_FAILED;
} // Semaphore::Valid()

bool Semaphore::Post() {
   if (!Valid()) {
      return false;
   } // if
   return ::sem_post(semaphore)==0;
} // Semaphore::Post()

bool Semaphore::Try() {
   if (!Valid()) {
      return false;
   } // if
   return ::sem_trywait(semaphore)==0;
} // Semaphore::Try()

void Semaphore::Wait() {
   if (!Valid()) {
      return;
   } // if
   ::sem_wait(semaphore);
} // Semaphore::Wait()
