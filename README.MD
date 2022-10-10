# SBXN
## A native sandbox, for the joy of programming.

### What is SBXN?
SBXN stands for sanbox native. It is a "sandbox engine" that runs compiled shared libraries.
SBXN aims to be a creative environment for programmers (who prefer to program in C) to 
quickly prototype their algorithms and ideas. SBXN itself is a program which supplies most 
of the boilerplate functionality you would normally need for a creative application.
It is currently in its most intial stage of development, and does not have much functionality
to offer. This is hopefully about to change soon. 

### How does it work?
It hotloads shared libraries as soon as they're
compiled, and runs them. The runtime communicates with its client library using
- Function calls: The runtime calls an initializing function defined in the library when the 
library is loaded. It also calls an update function at a set frequency.
- Function pointers: When a library is loaded into SBXN, a struct with function pointers
is sent to it's initialization function. These functionpointers account for SBXN's API.

### How do you use it?
```#include "sbxn/sbxn.h"``` in your source file, and define the ```SBX_INIT``` and 
```SBX_UPDATE``` functions. Then compile the library, and run SBXN with it's file path as
its first argument.
An example of how this is done can be found in /test/test_main.c.
