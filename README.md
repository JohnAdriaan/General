# General library
This repository holds generic C++ classes for Linux and Windows environments.

As much as possible, the same source is used in each:

 - `Name.hh` - a C++ header file.
 - `Name.tt` - a C++ template file.
 - `Name.ii` - a C++ include file (does not stand alone).
 - `Name.cc` - a C++ source file.

Where they must differ, either of two strategies are used:

 - As much as possible, the differences are in the source file:
   - `Name.Linux.cc`
   - `Name.Windows.cc`
 - If necessary, `#define` and `#ifdef` are used.
