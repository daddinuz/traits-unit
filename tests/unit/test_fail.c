/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 09, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <traits/traits.h>
#include "traits-unit.h"

/*
 * Declare setups
 */
SetupDeclare(BadSetup);

/*
 * Declare teardowns
 */
TeardownDeclare(BadTeardown);

/*
 * Declare fixtures
 */
FixtureDeclare(BadSetupFixture);
FixtureDeclare(BadTeardownFixture);

/*
 * Declare features
 */
FeatureDeclare(BadSetupFeature);
FeatureDeclare(BadFeature);
FeatureDeclare(BadTeardownFeature);
FeatureDeclare(SegFaultFeature);

/*
 * Describe our test case
 */
Describe("ShouldNotPass",
         Trait(
                 "AssertionErrors",
                 Run(BadSetupFeature, BadSetupFixture),
                 Run(BadFeature),
                 Run(BadTeardownFeature, BadTeardownFixture)
         ),
         Trait(
                 "UnexpectedErrors",
                 Run(SegFaultFeature)
         )
)

/*
 * Define setups
 */
SetupDefine(BadSetup) {
    assert_true(false);
    printf(" [should not see this] ");
    return NULL;
}

/*
 * Define teardowns
 */
TeardownDefine(BadTeardown) {
    (void) traits_context;
    assert_true(false);
    printf(" [should not see this] ");
}

/*
 * Define fixtures
 */
FixtureDefine(BadSetupFixture, BadSetup, DefaultTeardown);
FixtureDefine(BadTeardownFixture, DefaultSetup, BadTeardown);

/*
 * Define features
 */
FeatureDefine(BadSetupFeature) {
    (void) traits_context;
    /* Just do nothing */
}

FeatureDefine(BadFeature) {
    (void) traits_context;
    assert_true(false);
    printf(" [should not see this] ");
}

FeatureDefine(BadTeardownFeature) {
    (void) traits_context;
    /* Just do nothing */
}

FeatureDefine(SegFaultFeature) {
    (void) traits_context;
    /* De-referencing a null pointer */
    const int *x = traits_context;
    printf(" [should not see this: %d] ", *x);
}
