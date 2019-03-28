//
// Semaphore.Global.hh
//

#ifndef Semaphore_Global_hh
#define Semaphore_Global_hh

#include "Semaphore.hh"

class MT::Semaphore::Global : public Semaphore {

public: // Enums

   enum Creates {
      Exists,   // Open only if exists
      Create,   // Create if doesn't exist
      Exclusive // Only open if doesn't exist
   }; // Creates

public: // Methods

   // Create named (global) Semaphore. Will (by default) Unlink() in destructor
   explicit Global(const char *name, Creates create=Exists, unsigned start=0);

   // Attempt to create named (global) Semaphore.
   // If created, 'already' will be false, and Semaphore will (by default) be Unlink()ed in destructor.
   // Otherwise, attempt to open existing Semaphore.
   // If opened, 'already' will be true, and Semaphore will NOT (by default) be Unlink()ed in destructor.
   // Otherwise, Valid() will be false.
   Global(const char *name, bool &already);

   void Close();

   // Remove named Semaphore from future Opens
   void Unlink();

   // Do Unlink() in destructor - or not
   void SetUnlink(bool doUnlink);

   ~Global();

private: // Variables

   const char *name;

   bool unlink;

}; // Semaphore::Global

#endif // Semaphore_Global_hh
