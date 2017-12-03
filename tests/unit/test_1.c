/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 09, 2017 
 */

#include <traits/traits.h>
#include "traits-unit.h"

/*
 * Define features
 */
FeatureDefine(TrueMustBeTrue) {
    (void) traits_context;
    assert_true(true);
}

FeatureDefine(FalseMustBeFalse) {
    (void) traits_context;
    assert_false(false);
}

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
