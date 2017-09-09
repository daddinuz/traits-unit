/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 02, 2017 
 */

#include <stdio.h>
#include <stdlib.h>
#include "traits.h"
#include "traits-unit.h"

/*
 * Subject
 */
typedef struct MySubject *MySubject;

/*
 * Setup declaration
 */
SetupDeclare(GoodSetup);
SetupDeclare(BadSetup);

/*
 * Teardown declaration
 */
TeardownDeclare(GoodTeardown);
TeardownDeclare(BadTeardown);

/*
 * Fixture declaration
 */
FixtureDeclare(GoodFixture);
FixtureDeclare(BadSetupFixture);
FixtureDeclare(BadTeardownFixture);

/*
 * Features declaration
 */
FeatureDeclare(MySubjectTraitGoodFeature);
FeatureDeclare(MySubjectTraitBadFeature);

/*
 * Describe
 */
Describe("MySubject",
         Trait(
                 "MySubjectTraitX",
                 Run(MySubjectTraitGoodFeature),
                 Skip(MySubjectTraitBadFeature),
                 Todo(MySubjectTraitBadFeature)
         ),
         Trait(
                 "MySubjectTraitY",
                 Run(MySubjectTraitGoodFeature, BadSetupFixture),
                 Run(MySubjectTraitBadFeature, GoodFixture),
                 Run(MySubjectTraitGoodFeature, BadTeardownFixture),
                 Run(MySubjectTraitGoodFeature, GoodFixture)
         )
)

/*
 * Setup implementation
 */
SetupDefine(GoodSetup) {
    printf(" <GoodSetup> ");
    return malloc(32);
}

SetupDefine(BadSetup) {
    printf(" <BadSetup> ");
    assert_true(false);
    printf(" [should not see this] ");
    return NULL;
}

/*
 * Teardown implementation
 */
TeardownDefine(GoodTeardown) {
    printf(" <GoodTeardown> ");
    free(traits_context);
}

TeardownDefine(BadTeardown) {
    printf(" <BadTeardown> ");
    free(traits_context);
    assert_true(false);
    printf(" [should not see this] ");
}

/*
 * Fixture definition
 */
FixtureDefine(GoodFixture, GoodSetup, GoodTeardown);
FixtureDefine(BadSetupFixture, BadSetup, GoodTeardown);
FixtureDefine(BadTeardownFixture, GoodSetup, BadTeardown);

/*
 * Features implementation
 */
FeatureDefine(MySubjectTraitGoodFeature) {
    (void) traits_context;
    printf(" <MySubjectTraitGoodFeature> ");
}

FeatureDefine(MySubjectTraitBadFeature) {
    (void) traits_context;
    printf(" <MySubjectTraitBadFeature> ");
    assert_true(false);
    printf(" [ShouldNotSeeThis] ");
}
