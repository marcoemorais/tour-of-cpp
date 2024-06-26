# tour-of-cpp

This repo is inspired by many of the concise examples of idiomatic modern C++ that appear in the book _A Tour of C++_ by Bjarne Stroustrup. I initially started the repo to expand and experiment with the specific examples from the book, but I have since added a lot of new examples of modern C++ features that are not from the book.

```
@book{stroustrup2018tour,
  title={A Tour of C++},
  author={Stroustrup, Bjarne},
  year={2018},
  publisher={Addison-Wesley Professional}
}
```

Find more information about the book at the link below:

https://www.stroustrup.com/Tour.html

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
* [recursive_lambdas.cc](06-templates/recursive_lambdas.cc)
    * Demonstrate methods for creating recursive lambda functions.
* [tuple_apply.cc](06-templates/tuple_apply.cc)
    * Apply a function to every member of tuple using fold expression.

## 07-concepts-and-generic-programming

### Code

* [printf.cc](07-concepts-and-generic-programming/printf.cc)
    * Implement typesafe version of printf using variadic templates.

## 08-library-overview

### Code

## 09-strings-and-regular-expressions

### Code

* [stringops.cc](09-strings-and-regular-expressions/stringops.cc)
    * Demonstrate operations in std::string.
* [catstringview.cc](09-strings-and-regular-expressions/catstringview.cc)
    * Demonstrate operations in std::string_view.
* [regexops.cc](09-strings-and-regular-expressions/regexops.cc)
    * Demonstrate operations in std::regex.
* [csvparsers.cc](09-strings-and-regular-expressions/csvparsers.cc)
    * All the different ways to parse a csv.

## 10-input-and-output

### Code

* [anytoany.cc](10-input-and-output/anytoany.cc)
    * Demonstrate use of std::stringstream for any-to-any conversion.
* [readfile.cc](10-input-and-output/readfile.cc)
    * Read a file line-by-line raising std::runtime_error if error.

## 11-containers

### Code

* [customhash.cc](11-containers/customhash.cc)
    * Demonstrate use of custom hash functions with containers.
* [erase_remove.cc](11-containers/erase_remove.cc)
    * Demonstrate the erase-remove idiom to remove elements from containers.
* [hash_combine.cc](11-containers/hash_combine.cc)
    * Demonstrate combining hash functions.
* [inserter.cc](11-containers/inserter.cc)
    * Demonstrate use of std::inserter for adding elements to container.
* [mapinsert.cc](11-containers/mapinsert.cc)
    * Demonstrate different ways to insert into a unordered_map.
* [priority_queue.cc](11-containers/priority_queue.cc)
    * Demonstrate std::priority_queue using lambda functions for ordering.
* [rangecheckvec.cc](11-containers/rangecheckvec.cc)
    * Demonstrate using composition to obtain range-checked std::vector.
* [vecemplace.cc](11-containers/vecemplace.cc)
    * Demonstrate use of template forwarding for emplace into container.
* [vecsizecap.cc](11-containers/vecsizecap.cc)
    * Demonstrate size and capacity of std::vector with reserve, resize, clear, and shrink_to_fit.

## 12-algorithms

### Code

* [all_any_none_of.cc](12-algorithms/all_any_none_of.cc)
    * all_any_none_of demonstrates logical algorithms using bind.
* [findall.cc](12-algorithms/findall.cc)
    * Implement template function findall that demonstrates use of type alias.
* [first_less_than.cc](12-algorithms/first_less_than.cc)
    * first_less_than complements lower_bound and upper_bound.
* [heap_ops.cc](12-algorithms/heap_ops.cc)
    * Demonstrate heap functions in std::algorithms.
* [parallelsort.cc](12-algorithms/parallelsort.cc)
    * Demonstrate std::execution policies for parallel and/or vectorized sorting.
* [partial_sum.cc](12-algorithms/partial_sum.cc)
    * partial_sum implements cumsum and factorial.
* [set_ops.cc](12-algorithms/set_ops.cc)
    * set_ops demonstrates union, intersection, and (symmetric)difference.
* [unique.cc](12-algorithms/unique.cc)
    * Implement function template equivalent to std::unique for removing adjacent duplicate values.
* [wordcount.cc](12-algorithms/wordcount.cc)
    * Emit word frequency count based on input read from stdin.

## 13-utilities

### Code

* [bitsetops.cc](13-utilities/bitsetops.cc)
    * Demonstrate operations in std::bitset.
* [iterator_traits.cc](13-utilities/iterator_traits.cc)
    * Implement traits-based function overload with type aliases.
* [optional.cc](13-utilities/optional.cc)
    * Demonstrate use of std::optional.
* [pairtuple.cc](13-utilities/pairtuple.cc)
    * Demonstrate use of std::pair and std::tuple.
* [smartptr.cc](13-utilities/smartptr.cc)
    * Demonstrate use of std::unique_ptr and std::shared_ptr.
* [span.cc](13-utilities/span.cc)
    * Span is a (pointer,count) pair with support for range-based for loop.
* [swap.cc](13-utilities/swap.cc)
    * Demonstrate exception safe swap implemented using std::move.
* [timeit.cc](13-utilities/timeit.cc)
    * Demonstrate use of std::chrono for microbenchmarking.
* [rng_iterator.cc](13-utilities/rng_iterator.cc)
    * An iterator that returns an infinite sequence of random integers.

## 14-numerics

### Code

* [random.cc](14-numerics/random.cc)
    * Demonstrate use of pseudorandom number generators in std::random.

## 15-concurrency

### Code
* [counter.cc](15-concurrency/counter.cc)
    * Demonstrate use of mutex for sharing counter across threads.
* [deadlock.cc](15-concurrency/deadlock.cc)
    * Demonstrate use of scoped_lock with pairs of locks to avoid deadlock.
* [events.cc](15-concurrency/events.cc)
    * Demonstrate use of std::condition_variable for communicating events to listeners.
* [starvation.cc](15-concurrency/starvation.cc)
    * Demonstrate thread starvation between greedy and polite worker threads.
* [thread.cc](15-concurrency/thread.cc)
    * Demonstrate initializing std::thread with function and functor.


