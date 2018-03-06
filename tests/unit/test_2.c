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
                 Run(TrueMustBeTrue),
                 Run(FalseMustBeFalse)
         )
)

/*
 * Define features
 */
FeatureDefine(TrueMustBeTrue) {
    (void) traits_unit_context;
    assert_true(true);
}

FeatureDefine(FalseMustBeFalse) {
    (void) traits_unit_context;
    assert_false(false);
}
