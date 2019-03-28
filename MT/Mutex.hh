//
// Mutex.hh
//

#ifndef Mutex_hh
#define Mutex_hh

#include "MT.hh"

class MT::Mutex : private _Mutex_ {

public: // Classes

   class Lock; friend Lock;

public: // Methods

   Mutex();

   ~Mutex();

private: // Methods

   Mutex(const Mutex &) = delete;

private: // Variables

   MUTEXTYPE mutex;

}; // Mutex

#endif // Mutex_hh
