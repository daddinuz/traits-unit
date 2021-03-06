/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <traits-unit.h>
#include <traits/traits.h>

/*
 * Declare setups
 * Suppose saved on: setups.h
 */
Setup(SetupTrueMustBeTrue);
Setup(SetupFalseMustBeFalse);

/*
 * Declare teardowns
 * Suppose saved on: teardowns.h
 */
Teardown(TeardownTrueMustBeTrue);
Teardown(TeardownFalseMustBeFalse);

/*
 * Declare fixtures
 * Suppose saved on: fixtures.h
 */
Fixture(FixtureTrueMustBeTrue);
Fixture(FixtureFalseMustBeFalse);

/*
 * Declare features
 * Suppose saved on: features.h
 */
Feature(TrueMustBeTrue);
Feature(FalseMustBeFalse);

/*
 * Describe our test case
 */
Describe("TraitsUnitFramework",
         Trait("ShouldPass",
               Run(TrueMustBeTrue, FixtureTrueMustBeTrue),
               Run(FalseMustBeFalse, FixtureFalseMustBeFalse)
         )
)

/*
 * Define setups
 * Suppose saved on: setups.c
 */
Setup(SetupTrueMustBeTrue) {
    bool *context = malloc(sizeof(*context));
    *context = true;
    return context;
}

Setup(SetupFalseMustBeFalse) {
    bool *context = malloc(sizeof(*context));
    *context = false;
    return context;
}

/*
 * Define teardowns
 * Suppose saved on: teardowns.c
 */
Teardown(TeardownTrueMustBeTrue) {
    free(traitsUnit_getContext());
}

Teardown(TeardownFalseMustBeFalse) {
    free(traitsUnit_getContext());
}

/*
 * Define fixtures
 * Suppose saved on: fixtures.c
 */
FixtureImplements(FixtureTrueMustBeTrue, SetupTrueMustBeTrue, TeardownTrueMustBeTrue);
FixtureImplements(FixtureFalseMustBeFalse, SetupFalseMustBeFalse, TeardownFalseMustBeFalse);

/*
 * Define features
 * Suppose saved on: features.c
 */
Feature(TrueMustBeTrue) {
    bool *sut = traitsUnit_getContext();
    assert_true(*sut);
}

Feature(FalseMustBeFalse) {
    bool *sut = traitsUnit_getContext();
    assert_false(*sut);
}
