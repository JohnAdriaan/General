//
// Semaphore.hh
//

#ifndef Semaphore_hh
#define Semaphore_hh

#include "MT.hh"

class MT::Semaphore : private _MT_ {

public: // Classes

   // Local (unnamed) Semaphore
   class Local;

   // Global (named) Semaphore
   class Global;

public: // Methods

   bool Valid() const;

   bool Post();

   // Returns false if would wait.
   // Returns true if Semaphore claimed
   bool Try();

   void Wait();

protected: // Methods

   explicit Semaphore(SEMAPHORETYPE semaphore);

protected: // Variables

   SEMAPHORETYPE semaphore;

private: // Methods

   explicit Semaphore(const Semaphore &) = delete;

}; // Semaphore

#endif // Semaphore_hh
