//
// Adress.Linux.cc
//

#include "Address.hh"

using namespace BSD;

Address::Address(word protocol, int index, const byte* addr, byte addrLen) :
   link({ AF_PACKET, htons(protocol), index, 0,
           PACKET_OTHERHOST, addrLen, { 0 } }) {
   if (addr == nullptr) {
      return;
   } // if
   if (addrLen > sizeof link.sll_addr) {
      addrLen = sizeof link.sll_addr;
   } // if
   for (unsigned i = 0; i < addrLen; ++i) {
      link.sll_addr[i] = addr[i];
   } // for
} // Address::Address(protocol,index,addr,addrLen)
