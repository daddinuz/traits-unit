/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <traits-unit.h>
#include <traits/traits.h>

/*
 * Declare features
 * Suppose saved on: features.h
 */
FeatureDeclare(SignalsHandling);

/*
 * Describe our test case
 */
Describe("TraitsUnitFramework",
         Trait("ShouldPass",
               Run(SignalsHandling)
         )
)

/*
 * Define features
 * Suppose saved on: features.c
 */
FeatureDefine(SignalsHandling) {
    const size_t wrapped_signals_counter = traits_unit_get_wrapped_signals_counter();

    traits_unit_wraps(SIGINT) {
        /* this code will not raise */
    }
    assert_equal(wrapped_signals_counter, traits_unit_get_wrapped_signals_counter());

    traits_unit_wraps(SIGINT) {
        raise(SIGINT);
    }
    assert_equal(wrapped_signals_counter + 1, traits_unit_get_wrapped_signals_counter());

    traits_unit_wraps(SIGABRT) {
        abort();
    }
    assert_equal(wrapped_signals_counter + 2, traits_unit_get_wrapped_signals_counter());

    traits_unit_wraps(SIGSEGV) {
        raise(SIGSEGV);
    }
    assert_equal(wrapped_signals_counter + 3, traits_unit_get_wrapped_signals_counter());
}
