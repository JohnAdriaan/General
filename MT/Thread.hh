//
// Thread.hh
//

#ifndef Thread_hh
#define Thread_hh

#include "MT.hh"

class MT::Thread : private _MT_ {

public: // Attr

   class Attr;

   static const Attr joinable;

   static const Attr detached;

protected: // Methods

   Thread();

   bool Valid() const;

   bool Start(const Attr &attr=Thread::detached);

   virtual ~Thread() = default;

private: // Hooks

   hook void *Run() pure;

private: // Variables

   THREADTYPE thread;

private: // Static methods

   static void *Run(void *parameter);

}; // Thread

#endif // Thread_hh
