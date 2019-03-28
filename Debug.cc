//
// Debug.cc
//

#if 1

#ifndef NDEBUG

#include <new>
#include <iostream>

#include <malloc.h>

#include "General.hh"

class List : private _General_ {
public: // Classes
   class Block; friend Block;
private:
   List();
   void Link(Block &block);
   void Unlink(const Block &block);
   ~List();
private: // Variables
   Block *head;
   Block *tail;
   unsigned total;
   unsigned count;
private: // Static variables
   static List list;
}; // List

class List::Block : private _General_ {
friend List;
public: // Methods
   inline void Link(size_t size);
   inline void Unlink();
private: // Variables
   Block *prev;
   Block *next;
   size_t size;
}; // List::Block

List List::list;

List::List() :
      head(nullptr),
      tail(nullptr),
      total(0),
      count(0) {
   std::cerr << "Checking allocations" << std::endl;
} // List::List()

void List::Link(Block &block) {
   if (head==nullptr) {
      head = &block;
   } // if
   if (tail!=nullptr) {
      tail->next = &block;
   } // if
   block.prev = tail;
   tail = &block;
   ++count;
   ++total;
} // List::Link(Block)

void List::Unlink(const Block &block) {
   if (head==&block) {
      head = block.next;
   } // if
   if (tail==&block) {
      tail = block.prev;
   } // if
   --count;
// --total; // That's the POINT!
} // List::Unlink(Block)

List::~List() {
   std::cerr << "There were " << total
             << " blocks allocated in total." << std::endl;
   std::cerr << "There were " << count
             << " blocks that weren't deleted"
             << (count == 0 ? '.' : ':')
             << std::endl;;
   if (count==0) {
      return;
   } // if

   Block *ptr = head;
   while (ptr!=nullptr) {
      std::cerr << ptr->size;
      bool chars = true;
      char *s = (char *)(ptr+1);
      for (unsigned i=0;i<ptr->size;++i) {
         char c = *s++;
         if (c=='\0') {
            break;
         } // if
         if ((c=='\t') || (c=='\n') || (c=='\r')) {
            continue;
         } // if
         if ((c<' ') || (c>'~')) {
            chars = false;
            break;
         } // if
      } // for
      if (chars) {
         std::cerr << ": " << (const char *)(ptr+1);
      } // if
      std::cerr << std::endl;
      ptr = ptr->next;
   } // while
   std::cerr << std::endl;
} // List::~List()

inline void List::Block::Link(size_t newSize) {
   next = nullptr;
   size = newSize;
   List::list.Link(*this);
} // Block::Link(newSize)

inline void List::Block::Unlink() {
   if (prev!=nullptr) {
      prev->next = next;
   } // if
   if (next!=nullptr) {
      next->prev = prev;
   } // if
   List::list.Unlink(*this);
} // Block::Unlink()

void * operator new(size_t size) {
   List::Block* block = (List::Block*)::malloc(sizeof(List::Block) + size);
   if (block == nullptr) {
      return nullptr;
   } // if
   block->Link(size);
   return block + 1;
} // operator new(size)

void operator delete(void *ptr) {
   if (ptr==nullptr) {
      return;
   } // if
   List::Block *block = ((List::Block *)ptr)-1;
   block->Unlink();
   ::free(block);
} // operator delete(ptr)

#endif // !NDEBUG

#endif // 1 || 0
