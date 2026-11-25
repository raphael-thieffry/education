# `copy_ptr`

## General instructions

As usual:

```sh
mkdir build
cd build
cmake ../
make
```

## Part 1: `copy_ptr` semantics

We want a "smart pointer" like `std::unique_ptr` with a move semantic similar to
it, as well as additional copy semantics that perform a copy of the object being
pointed (see `tests/copy_ptr.cpp`).

The semantic must ensure:
- to move and copy objects while ensuring that a pair of pointers will never
  point to the same object,
- that objects pointed by `copy_ptr` are properly destroyed,
- that objects held by `copy_ptr` aren't destroyed more than once.

For that, implement all the methods in `include/copy_ptr.hpp`:

- move/copy constructors
- move/copy assign operators (`operator=`)
- destructor
- `operator*`, `operator->`, `get()`, `swap()`, `operator bool()`,
  etc. (ie. all members that contain `// TODO`)

Run `make` to compile and execute tests for this part of the project.

## Partie 2: Quid du polymorphisme?

A problem occurs when we use `copy_ptr` with polymorphic classes
(ie. classes with inheritance). A child class stored in a parent class can be
sliced if the child class has additional members, which can cause data loss and
runtime errors.

Modify `copy_ptr` to ensure that to ensure that copying calls the `clone()`
virtual method of the pointed element to obtain a fresh pointer to a copy
of the object. Each child class will have to overload `clone()` to implement
its own cloning method.

Tests in `tests/copy_ptr_poly.cpp` may serve as examples to guide you for
implementing that.

NB: You can use [the `is_polymorphic` type trait](
https://en.cppreference.com/w/cpp/types/is_polymorphic) to detect polymorphic
types.

Run `make run_test_copy_ptr_poly` to compile and execute tests for this part of
the project.
