/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 02, 2017 
 */

#include <stdio.h>
#include "traits-unit.h"

/*
 * Subject
 */
typedef struct MySubject *MySubject;

/*
 * Setup declaration
 */
SetupDeclare(GoodSetup);

/*
 * Teardown declaration
 */
TeardownDeclare(GoodTeardown);

/*
 * Fixture declaration
 */
FixtureDeclare(GoodFixture);

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
                 Run(MySubjectTraitYFeature2, GoodFixture),
                 Run(MySubjectTraitYFeature3, GoodFixture)
         )
)

/*
 * Setup implementation
 */
SetupDefine(GoodSetup) {
    printf(" <GoodSetup> ");
    return NULL;
}

/*
 * Teardown implementation
 */
TeardownDefine(GoodTeardown) {
    (void) traits_context;
    printf(" <GoodTeardown> ");
}

/*
 * Fixture definition
 */
FixtureDefine(GoodFixture, GoodSetup, GoodTeardown);

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
}

FeatureDefine(MySubjectTraitYFeature2) {
    (void) traits_context;
    printf(" <MySubjectTraitYFeature2> ");
}

FeatureDefine(MySubjectTraitYFeature3) {
    (void) traits_context;
    printf(" <MySubjectTraitYFeature3> ");
}
