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
SetupDeclare(SetupTrueMustBeTrue);
SetupDeclare(SetupFalseMustBeFalse);

/*
 * Declare teardowns
 */
TeardownDeclare(TeardownTrueMustBeTrue);
TeardownDeclare(TeardownFalseMustBeFalse);

/*
 * Declare fixtures
 */
FixtureDeclare(FixtureTrueMustBeTrue);
FixtureDeclare(FixtureFalseMustBeFalse);

/*
 * Declare features
 */
FeatureDeclare(TrueMustBeTrue);
FeatureDeclare(FalseMustBeFalse);

/*
 * Describe our test case
 */
Describe("ShouldPass",
         Trait(
                 "Boolean",
                 Run(TrueMustBeTrue, FixtureTrueMustBeTrue),
                 Run(FalseMustBeFalse, FixtureFalseMustBeFalse)
         )
)

/*
 * Define setups
 */
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
TeardownDefine(TeardownTrueMustBeTrue) {
    free(traits_unit_context);
}

TeardownDefine(TeardownFalseMustBeFalse) {
    free(traits_unit_context);
}

/*
 * Define fixtures
 */
FixtureDefine(FixtureTrueMustBeTrue, SetupTrueMustBeTrue, TeardownTrueMustBeTrue);
FixtureDefine(FixtureFalseMustBeFalse, SetupFalseMustBeFalse, TeardownFalseMustBeFalse);

/*
 * Define features
 */
FeatureDefine(TrueMustBeTrue) {
    bool *sut = traits_unit_context;
    assert_true(*sut);
}

FeatureDefine(FalseMustBeFalse) {
    bool *sut = traits_unit_context;
    assert_false(*sut);
}
