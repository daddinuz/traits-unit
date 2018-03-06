/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   March 06, 2018
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
