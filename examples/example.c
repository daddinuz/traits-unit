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
SetupDeclare(MySubjectTraitYSetup);

/*
 * Teardown declaration
 */
TeardownDeclare(MySubjectTraitYTeardown);

/*
 * Fixture declaration
 */
FixtureDeclare(MySubjectTraitYFixture);

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
                 Run(MySubjectTraitYFeature1, MySubjectTraitYFixture),
                 Run(MySubjectTraitYFeature2),
                 Run(MySubjectTraitYFeature3, MySubjectTraitYFixture)
         )
)

/*
 * Setup implementation
 */
SetupDefine(MySubjectTraitYSetup) {
    printf(" <MySubjectTraitYSetup> ");
    return NULL;
}

/*
 * Teardown implementation
 */
TeardownDefine(MySubjectTraitYTeardown) {
    (void) traits_context;
    printf(" <MySubjectTraitYTeardown> ");
}

/*
 * Fixture definition
 */
FixtureDefine(MySubjectTraitYFixture, MySubjectTraitYSetup, MySubjectTraitYTeardown);

/*
 * Features implementation
 */
FeatureDefine(MySubjectTraitXFeature1) {
    (void) traits_context;
    printf(" <MySubjectTraitXFeature1> ");
    assert_true(false);
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
}

FeatureDefine(MySubjectTraitYFeature2) {
    (void) traits_context;
    printf(" <MySubjectTraitYFeature2> ");
}

FeatureDefine(MySubjectTraitYFeature3) {
    (void) traits_context;
    printf(" <MySubjectTraitYFeature3> ");
}
