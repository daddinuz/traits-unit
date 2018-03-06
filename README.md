Traits Unit
===========

[![Build Status](https://travis-ci.org/daddinuz/traits-unit.svg?branch=master)](https://travis-ci.org/daddinuz/traits-unit)

Traits Unit is a unit test framework written in C99 inspired by major unit testing frameworks in other languages.
It supports **test automation**, sharing of **setup** and **teardown** code for tests, **aggregation of tests** into groups,
test result **report**, with no need for runners or external scripts that generate your test code.
Each test has its own **separate address space**, so that assertion failures, signals or code errors that may cause
**faults are handled** and reported.

Even if designed to work with [traits](https://github.com/daddinuz/traits), the framework itself does not
provide any assertions library so that you can choose the one you prefer that satisfies those requirements:
 * print error messages on **stderr**.
 * terminate the process calling **exit** from stdlib in case of assertion errors.

See the `tests` folder for an overview of the framework.
