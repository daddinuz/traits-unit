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
    assert_true(true);
}

FeatureDefine(SkippedFeature) {
    assert_true(false);
}

FeatureDefine(NotImplementedFeature) {

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
