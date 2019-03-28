//
// Thread.cc
//

#include "Thread.Attr.hh"

using namespace MT;

const Thread::Attr Thread::joinable(Thread::Attr::Joinable);
const Thread::Attr Thread::detached(Thread::Attr::Detached);

enum { Invalid = (THREADTYPE)INVALID };

Thread::Thread() :
        thread(Invalid) {
} // Thread::Thread()

bool MT::Thread::Valid() const {
   return thread != Invalid;
} // Thread::Valid()

bool Thread::Start(const Attr &attr /*=detached*/) {
   return ::pthread_create(&thread, attr, &Thread::Run, this)==0;
} // Thread::Start(Attr)

void *Thread::Run(void *parameter) {
   Thread *thread = (Thread *)parameter;
   return thread->Run();
} // Thread::Run(parameter)
