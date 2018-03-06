/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
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
#include <traits/traits.h>
#include "traits-unit.h"

/*
 * Declare setups
 */
SetupDeclare(SetupStringMustBeString);
SetupDeclare(SetupTrueMustBeTrue);
SetupDeclare(SetupFalseMustBeFalse);

/*
 * Declare teardowns
 */
TeardownDeclare(TeardownStringMustBeString);
TeardownDeclare(TeardownTrueMustBeTrue);
TeardownDeclare(TeardownFalseMustBeFalse);

/*
 * Declare fixtures
 */
FixtureDeclare(FixtureStringMustBeString);
FixtureDeclare(FixtureTrueMustBeTrue);
FixtureDeclare(FixtureFalseMustBeFalse);

/*
 * Declare features
 */
FeatureDeclare(NullMustBeNull);
FeatureDeclare(StringMustBeString);

FeatureDeclare(TrueMustBeTrue);
FeatureDeclare(FalseMustBeFalse);

/*
 * Describe our test case
 */
Describe("ShouldPass",
         Trait(
                 "Pointers",
                 Run(NullMustBeNull),
                 Run(StringMustBeString, FixtureStringMustBeString)
         ),
         Trait(
                 "Boolean",
                 Run(TrueMustBeTrue, FixtureTrueMustBeTrue),
                 Run(FalseMustBeFalse, FixtureFalseMustBeFalse)
         )
)

/*
 * Define setups
 */
SetupDefine(SetupStringMustBeString) {
    char *context = strdup("Hello World!");
    return context;
}

SetupDefine(SetupTrueMustBeTrue) {
    bool *context = malloc(sizeof(*context));
    *context = true;
    return context;
}

SetupDefine(SetupFalseMustBeFalse) {
    bool *context = malloc(sizeof(*context));
    *context = false;
    return context;
}

/*
 * Define teardowns
 */
TeardownDefine(TeardownStringMustBeString) {
    free(traits_unit_get_context());
}

TeardownDefine(TeardownTrueMustBeTrue) {
    free(traits_unit_get_context());
}

TeardownDefine(TeardownFalseMustBeFalse) {
    free(traits_unit_get_context());
}

/*
 * Define fixtures
 */
FixtureDefine(FixtureStringMustBeString, SetupStringMustBeString, TeardownStringMustBeString);
FixtureDefine(FixtureTrueMustBeTrue, SetupTrueMustBeTrue, TeardownTrueMustBeTrue);
FixtureDefine(FixtureFalseMustBeFalse, SetupFalseMustBeFalse, TeardownFalseMustBeFalse);

/*
 * Define features
 */
FeatureDefine(NullMustBeNull) {
    assert_null(NULL);
}

FeatureDefine(StringMustBeString) {
    const char *sut = traits_unit_get_context();
    assert_string_equal("Hello World!", sut);
}

FeatureDefine(TrueMustBeTrue) {
    bool *sut = traits_unit_get_context();
    assert_true(*sut);
}

FeatureDefine(FalseMustBeFalse) {
    bool *sut = traits_unit_get_context();
    assert_false(*sut);
}
