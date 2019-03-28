//
// FD.hh
//

#ifndef FD_hh
#define FD_hh

#include "../General.hh"
#include "../String/String.hh"

class _FD_ : private _General_ {
}; // _FD_

template <typename T>
class FD : private _FD_ {

public: // Constants

   static const unsigned MaxSendFile = 0x7FFF0000;

public: // Methods

   inline bool Valid() const;

   // Returns false on error.
   // Returns true, but read==0, for end of file
   bool Read(void *buffer, Size size, Size &read);

   // Doesn't return until all written - or error
   bool Write(const String &string);

   // Doesn't return until all written - or error
   bool Write(const void *buffer, Size size);

   bool Write(const void *buffer, Size size, Size &wrote);

   bool SendFile(FD &source, Size length=MaxSendFile);

   void Close();

protected: // Typedefs

   typedef T Type;

protected: // Methods

   explicit FD(Type fd=Invalid);

   explicit FD(FD &fd);

   bool Error(int result, const char *call);

   int IOCtl(int request, void *result);

   ~FD();

protected: // Variables

   Type fd;

private: // Variables

   int err; // Saved errno

private: // Enums

   enum { Invalid = (Type)-1 };

}; // FD

template <typename T>
inline bool FD<T>::Valid() const {
   return fd!=Invalid;
} // FD::Valid()

#ifdef NDEBUG
template <typename T>
inline bool FD<T>::Error(int result, const char * /*call*/) {
   return result==-1 ?
          (err=errno, false) :
          true;
} // FD::Error(result,call)

#define Test(x) Error((int)x,nullptr) // Don't embed function call as a string
#else  // NDEBUG
#define Test(x) Error((int)x,#x)      // Embeds function call as a string
#endif // !NDEBUG

#endif // FD_hh
