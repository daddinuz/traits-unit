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
FeatureDeclare(ShouldRaise);

/*
 * Describe our test case
 */
Describe("ShouldPass",
         Trait(
                 "Signals",
                 Run(ShouldRaise)
         )
)

/*
 * Define features
 */
FeatureDefine(ShouldRaise) {
    (void) traits_unit_context;
    const size_t handled_signals = traits_unit_get_handled_signals_counter();

    traits_unit_with_raises(SIGINT) {
        raise(SIGINT);
    }
    assert_equal(handled_signals + 1, traits_unit_get_handled_signals_counter());

    traits_unit_with_raises(SIGABRT) {
        abort();
    }
    assert_equal(handled_signals + 2, traits_unit_get_handled_signals_counter());

    traits_unit_with_raises(SIGSEGV) {
        raise(SIGSEGV);
    }
    assert_equal(handled_signals + 3, traits_unit_get_handled_signals_counter());
}
