//
// MT.hh
//

#ifndef MT_hh
#define MT_hh

#ifdef _MSC_VER

   #include "../Windows/Windows.hh"

   #define THREADTYPE    HANDLE
   #define MUTEXTYPE     HANDLE
   #define SEMAPHORETYPE HANDLE

   #define INVALID       INVALID_HANDLE_VALUE

#endif // _MSC_VER

#ifdef __GNUC__

   #include <pthread.h>
   #include <semaphore.h>

   #define THREADTYPE    pthread_t
   #define MUTEXTYPE     pthread_mutex_t
   #define SEMAPHORETYPE sem_t *

   #define INVALID      -1

#endif // __GNUC__

#include "../General.hh"

namespace MT {

   class _MT_;

   class _Mutex_;

   class Mutex;

   class NoMutex;

   class Semaphore;

   class Thread;

   class _Queue_;

   template <typename Type>
   struct Atomic;

   template <typename Element, class Mutex>
   class Queue;

} // MT

class MT::_MT_ : private _General_ {
}; // _MT_

class MT::_Mutex_ : private _MT_ {
protected:
   class _Lock_;
}; // _Mutex_

class MT::_Mutex_::_Lock_ : private _Mutex_ {
}; // _Mutex_::_Lock_

#endif // MT_hh
