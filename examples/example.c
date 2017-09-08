/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 02, 2017 
 */

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
FeatureDeclare(MySubjectTraitXFeature1);
FeatureDeclare(MySubjectTraitXFeature2);
FeatureDeclare(MySubjectTraitXFeature3);

FeatureDeclare(MySubjectTraitYFeature1);
FeatureDeclare(MySubjectTraitYFeature2);
FeatureDeclare(MySubjectTraitYFeature3);

/*
 * Describe
 */
Describe("MySubject",
         Trait(
                 "MySubjectTraitX",
                 Run(MySubjectTraitXFeature1),
                 Skip(MySubjectTraitXFeature2),
                 Todo(MySubjectTraitXFeature3)
         ),
         Trait(
                 "MySubjectTraitY",
                 Run(MySubjectTraitYFeature1, GoodFixture),
                 Run(MySubjectTraitYFeature2, BadSetupFixture),
                 Run(MySubjectTraitYFeature3, BadTeardownFixture)
         )
)

/*
 * Setup implementation
 */
SetupDefine(GoodSetup) {
    printf(" <GoodSetup> ");
    return NULL;
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
    (void) traits_context;
    printf(" <GoodTeardown> ");
}

TeardownDefine(BadTeardown) {
    (void) traits_context;
    printf(" <BadTeardown> ");
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
FeatureDefine(MySubjectTraitXFeature1) {
    (void) traits_context;
    printf(" <MySubjectTraitXFeature1> ");
}

FeatureDefine(MySubjectTraitXFeature2) {
    (void) traits_context;
    printf(" <MySubjectTraitXFeature2> ");
}

FeatureDefine(MySubjectTraitXFeature3) {
    (void) traits_context;
    printf(" <MySubjectTraitXFeature3> ");
}

FeatureDefine(MySubjectTraitYFeature1) {
    (void) traits_context;
    printf(" <MySubjectTraitYFeature1> ");
    assert_true(false);
    printf(" [should not see this] ");
}

FeatureDefine(MySubjectTraitYFeature2) {
    (void) traits_context;
    printf(" <MySubjectTraitYFeature2> ");
}

FeatureDefine(MySubjectTraitYFeature3) {
    (void) traits_context;
    printf(" <MySubjectTraitYFeature3> ");
}
