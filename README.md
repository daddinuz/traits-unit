Traits Unit
===========

[![Build Status](https://travis-ci.org/daddinuz/traits-unit.svg?branch=master)](https://travis-ci.org/daddinuz/traits-unit)

Traits Unit is a unit test framework written in C99 inspired by major unit testing frameworks in other languages.  
It supports **test automation**, sharing of **setup** and **teardown** code for tests, **aggregation of tests** into groups,
test results **report**, with no need for runners or external scripts that generate your code.
Each test has its own **separate address space**, so that assertion failures, signals or code errors that may cause
**faults are handled** and reported.

Even if designed to work with [traits](https://github.com/daddinuz/traits), the framework itself does not
require or provide any assertions library so that you can choose the one you prefer that satisfies those requirements:
 
 * print error messages on **stderr**.
 * terminate the process calling **exit**, **abort** or **raise** a signal in case of error (assert from assert.h is perfectly fine).

## Quick Overview

The dumbest test ever made

```c
#include <traits.h>
#include <traits-unit.h>

/*
 * Define features
 */
FeatureDefine(TrueMustBeTrue) {
    assert_true(true);
}

FeatureDefine(WouldFailNeedsFixes) {
    assert_true(false);
}

FeatureDefine(ACoolFeatureThatWillBeImplemented) {

}

FeatureDefine(AnotherCoolFeatureThatWillBeImplemented) {

}

/*
 * Describe our test case
 */
Describe("TraitsUnitFramework",
         Trait("ShouldPass",
               Run(TrueMustBeTrue),
               Skip(WouldFailNeedsFixes)
         ),
         Trait("TheBestIsYetToCome",
               Todo(ACoolFeatureThatWillBeImplemented),
               Todo(AnotherCoolFeatureThatWillBeImplemented),
         )
)
```

As you can see there's no need to provide a main function, the framework defines it automatically.  
Suppose the above example to be saved in file `traits_overview.c` and compiled with: 

`$ gcc traits_overview.c -ltraits-unit -o traits_overview`  

The produced binary, if ran without parameters will execute all the features registered with `Run` of every `Trait` in the `Describe` section.  
You can also provide the name of the specific traits you want to execute when running the binary as follow:  
`$ ./traits_overview ShouldPass`

#### Controlled signals handling

The framework itself will detect unhandled signals marking the raising feature as failed and reporting back the error.  
Sometimes you may want to ensure that your code, under certain circumstances, for example illegal arguments or unrecoverable errors, aborts the execution or raises some specific signal to notify the error.  
In order to do that, traits unit provides an helper macro that will wrap a specific portion of code allowing a specific 
signal to be raised and incrementing a counter of wrapped signals without terminating the running feature.

```c
#include <traits.h>
#include <traits-unit.h>

/*
 * Define features
 */
FeatureDefine(SignalsHandling) {
    const size_t wrapped_signals_counter = traits_unit_get_wrapped_signals_counter();

    traits_unit_wraps(SIGINT) {
        // this code will not raise
    }
    assert_equal(wrapped_signals_counter, traits_unit_get_wrapped_signals_counter());

    traits_unit_wraps(SIGILL) {
        printf("Wrapping: %s. ", strsignal(SIGILL));
        raise(SIGILL);
        printf("This line won't be reached.");
    }
    assert_equal(wrapped_signals_counter + 1, traits_unit_get_wrapped_signals_counter());

    traits_unit_wraps(SIGABRT) {
        printf("Wrapping: %s. ", strsignal(SIGABRT));
        abort();
        printf("This line won't be reached.");
    }
    assert_equal(wrapped_signals_counter + 2, traits_unit_get_wrapped_signals_counter());

    traits_unit_wraps(SIGSEGV) {
        printf("Wrapping: %s. ", strsignal(SIGSEGV));
        raise(SIGSEGV);
        printf("This line won't be reached.");
    }
    assert_equal(wrapped_signals_counter + 3, traits_unit_get_wrapped_signals_counter());
}

/*
 * Describe our test case
 */
Describe("TraitsUnitFramework",
         Trait("ShouldPass",
               Run(SignalsHandling)
         )
)
``` 
  
For a deeper overview of the framework please check the `tests` folder.
