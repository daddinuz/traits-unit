Traits Unit
===========

[![Build Status](https://travis-ci.org/daddinuz/traits-unit.svg?branch=master)](https://travis-ci.org/daddinuz/traits-unit)

Traits Unit is a unit test framework written in C99 inspired by major unit testing frameworks in other languages.  
It supports **test automation**, sharing of **setup** and **teardown** code for tests, **aggregation of tests** into groups,
test results **report**, with no need for runners or external scripts that generate your code.  
Each test has its own **separate address space**, so that assertion failures, signals or code that may cause **faults are handled** and reported.

Even if designed to work with [traits](https://github.com/daddinuz/traits), the framework itself does not
require or provide any assertions library so that you can choose the one you prefer that satisfies those requirements:
 
 * print error messages on **stderr**.
 * terminate the process calling **exit**, **abort** or **raise** a signal in case of error (`assert` macro from `assert.h` is perfectly fine).

## Quick Overview

```c
#include <traits.h>
#include <traits-unit.h>

/*
 * Define features
 */
Feature(ItWorks) {
    assert_true(true);
}

Feature(Fixme) {
    assert_true(false);
}

Feature(SignalsHandling) {
    const size_t wrappedSignalsCounter = traitsUnit_getWrappedSignalsCounter();
    assert_equal(wrappedSignalsCounter, traitsUnit_getWrappedSignalsCounter());

    traitsUnit_wrap(SIGSEGV) {
        printf("Wrapping: %s. ", strsignal(SIGSEGV));
        raise(SIGSEGV);
    }
    assert_equal(wrappedSignalsCounter + 1, traitsUnit_getWrappedSignalsCounter());

    traitsUnit_wrap(SIGABRT) {
        printf("Wrapping: %s. ", strsignal(SIGABRT));
        abort();
    }
    assert_equal(wrappedSignalsCounter + 2, traitsUnit_getWrappedSignalsCounter());
}

/*
 * Describe our test case
 */
Describe("TraitsUnitFramework",
         Trait("ShouldPass",
               Run(ItWorks),
               Skip(Fixme)
         ),
         Trait("TheBestIsYetToCome",
               Run(SignalsHandling)
         )
)
```

For a deeper overview of the framework please check the `tests/unit` folder.

As can be seen there's no need to provide the `main` function, the framework defines it automatically.  
Suppose the above example to be saved in file `traits_overview.c` and compiled with: 

`$ gcc traits_overview.c -ltraits-unit -o traits_overview`  

The produced binary, if ran without parameters will execute all the features registered with `Run` of every `Trait` in the `Describe` section.  
You can also provide the name of the specific traits you want to execute when running the binary as follow:  
`$ ./traits_overview ShouldPass`

#### Signals handling

The framework itself will detect unhandled signals marking the raising call as failed and reporting back the error.  
Sometimes you may want to ensure that your code, under certain circumstances, for example illegal arguments or unrecoverable errors, aborts the execution or raises some specific signal to notify the error.  
In order to do that, traits unit provides an helper macro that will wrap a specific portion of code allowing a specific 
signal to be raised and incrementing a counter of wrapped signals without terminating the running call.
