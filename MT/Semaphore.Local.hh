//
// Semaphore.Local.hh
//

#ifndef Semaphore_Local_hh
#define Semaphore_Local_hh

#include "Semaphore.hh"

class MT::Semaphore::Local : public Semaphore {

public: // Methods

   // Create local (unnamed) Semaphore
   explicit Local(unsigned start=0);

   void Close();

   ~Local();

private: // Variables

   sem_t sem;

}; // Semaphore::Local

#endif // Semaphore_Local_hh
