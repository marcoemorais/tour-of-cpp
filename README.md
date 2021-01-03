# tour-of-cpp

Exercises based on or inspired from reading:
```
@book{stroustrup2018toc,
    author = {B. Stroustrup},
    title = {A Tour of C++},
    year = {2018},
    isbn = {978-0-13-499783-4},
    publisher = {Addison-Wesley},
    edition = {2st}
}
```

See also: [Advice](ADVICE.html)

## Table of Contents

* [01-the-basics](#the-basics)
* [02-user-defined-types](#user-defined-types)
* [03-modularity](#modularity)
* [04-classes](#classes)
* [05-essential-operations](#essential-operations)
* [06-templates](#templates)
* [07-concepts-and-generic-programming](#concepts-and-generic-programming)
* [08-library-overview](#library-overview)
* [09-strings-and-regular-expressions](#strings-and-regular-expressions)
* [10-input-and-output](#input-and-output)
* [11-containers](#containers)
* [12-algorithms](#algorithms)
* [13-utilities](#utilities)
* [14-numerics](#numerics)
* [15-concurrency](#concurrency)

## 01-the-basics

### Code

* [forloop.cc](./01-the-basics/forloop.cc)
    * Demonstrate different forms of for-range syntax for array/vector containers.
* [helloworld.cc](./01-the-basics/helloworld.cc)
    * Hello World in modern c++.
* [if.cc](./01-the-basics/if.cc)
    * Go-style variable declaration as part of `if`.
* [init.cc](./01-the-basics/init.cc)
    * Various forms of literal initialization.
* [literal.cc](./01-the-basics/literal.cc)
    * Literal intiailization that emphasizes readability.
* [nullptr.cc](./01-the-basics/nullptr.cc)
    * Demonstrate use of `nullptr` as replacement for `NULL` macro.
* [pointer.cc](./01-the-basics/pointer.cc)
    * Demonstrate basic pointer operations and equivalencies.
* [printer.cc](./01-the-basics/printer.cc)
    * Template for printing containers.
* [ref.cc](./01-the-basics/ref.cc)
    * Demonstrate basic reference operations and distinction from pointers.
* [square.cc](./01-the-basics/square.cc)
    * Demonstrate `constexpr` for pure functions aka functions without side-effects.

## 02-user-defined-types

### Code

* [enum.cc](./02-user-defined-types/enum.cc)
    * Demonstrate `enum class` and use of operator overloading with enum.
* [read_and_sum.cc](./02-user-defined-types/read_and_sum.cc)
    * Read n integers from istream, c-style alloc/free functions.
* [variant.cc](./02-user-defined-types/variant.cc)
    * Demonstrate std::variant as an improvment of `union`.
* [vector1.cc](./02-user-defined-types/vector1.cc)
    * Repeat of `read_and_sum.cc`, but using cpp constructor/destructor.

## 03-modularity

### Code

* [base.cc](./03-modularity/base.cc)
    * Return a number as string in arbitrary base.
* [binding.cc](./03-modularity/binding.cc)
    * Demonstrate use of unpacking for multi-value return type.
* [rangemap.cc](./03-modularity/rangemap.cc)
    * Demonstrate use of unpacking and for-range syntax for map containers.
* [throwcatch.cc](./03-modularity/throwcatch.cc)
    * Demonstrate cpp convention of throw-by-value and catch by (const) reference.

## 04-classes

### Code

* [shapes.cc](./04-classes/shapes.cc)
    * Polymorphic hierarchy with pure virtual base class, container of unique_ptr to base class.
* [vector2.cc](./04-classes/vector2.cc)
    * Demonstrate use of std::initializer_list constructor.

## 05-essential-operations

### Code

* [mat3x3.cc](05-essential-operations/mat3x3.cc)
    * Demonstrate copy/move constructor and assignment for POD-type class.
* [vector3.cc](05-essential-operations/vector3.cc)
    * Demonstrate copy/move constructor and assignment for resource handle class.
* [uliteral.cc](05-essential-operations/uliteral.cc)
    * Demonstrate creating user-defined literals.

## 06-templates

### Code

* [accumulate.cc](06-templates/accumulate.cc)
    * Implement function template equivalent to std::accumulate.
* [count_if.cc](06-templates/count_if.cc)
    * Implement function template equivalent to std::count_if with UnaryPredicate.
* [for_each.cc](06-templates/for_each.cc)
    * Implement function template equivalent to std::for_each with UnaryFunction.

## 07-concepts-and-generic-programming

### Code

* [printf.cc](07-concepts-and-generic-programming/printf.cc)
    * Implement typesafe version of printf using variadic templates.

## 08-library-overview

### Code

## 09-strings-and-regular-expressions

### Code

## 10-input-and-output

### Code

## 11-containers

### Code

## 12-algorithms

### Code

## 13-utilities

### Code

## 14-numerics

### Code

## 15-concurrency

### Code

