/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   March 06, 2018
 */

#include <traits/traits.h>
#include "traits-unit.h"

/*
 * Define features
 */
FeatureDefine(TrueMustBeTrue) {
    (void) traits_unit_context;
    assert_true(true);
}

FeatureDefine(SkippedFeature) {
    (void) traits_unit_context;
    assert_true(false);
}

FeatureDefine(NotImplementedFeature) {
    (void) traits_unit_context;
}

/*
 * Describe our test case
 */
Describe("ShouldPass",
         Trait(
                 "Boolean",
                 Run(TrueMustBeTrue),
                 Skip(SkippedFeature),
                 Todo(NotImplementedFeature)
         )
)
