# CArray
## 1.0.0-build
## 20261025

CARR is a lightweight C vector library that stores pointers to elements (`void *`). It supports insertion, replacement, deletion, reversal, and dynamic resizing.

## Requirements

- **C standard:** C99 or later.
- **Compilers:** GCC, Clang, or MSVC. Other compilers *might* also support CArray
- **Minimum compiler versions:** GCC 3.0+, Clang 3.0+, or MSVC 2013+
- **Dependencies:** Standard C headers and the CARR implementation, no other dependencies needed

## Setup

Run the following commands from the project root:

```sh
./gen.sh
./gen.sh link
./compile.sh setup
./compile.sh settings
```

The interactive settings step (`./compile.sh settings`) is **optional**.

## Building Tests and Library Manually

Compile the project using:

```sh
./compile.sh
```

Run the compiled program tests using:

```sh
./run.sh
```

## Minimal Usage

Include the CARR header:

```c
#include "carray/carr.h"
```

Initialize a vector, add elements, reverse, delete an element, and destroy it:

```c
int a = 10;
int b = 20;

CARR vec = carr_init(4, true);

carr_pushBack(&vec, &a);
carr_pushBack(&vec, &b);
carr_pushFront(&vec, &b);

carr_replaceIndex(&vec, &a, 1);
carr_reverse(&vec);
carr_deleteIndex(&vec, 0, true);

carr_destroy(&vec);
```

Check returned `CARRError` values to handle operation failures.

## Notes

- CARR stores pointers rather than copies of elements. Ensure the pointed-to objects remain valid while they are used.
- `carr_init(4, true)` initializes the vector with a capacity of four and enables dynamic resizing.
- `carr_destroy()` releases the vector's internal resources; it does not necessarily free the pointed-to elements.
- The meaning of the `fall` parameter in `carr_deleteIndex()` depends on the implementation.

