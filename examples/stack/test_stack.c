/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 14, 2017 
 */

#include "stack.h"
#include "traits.h"
#include "traits-unit.h"

/*
 * Define data
 */
const char *const SEEDED_STACK_ELEMENTS[] = {"Element One", "Element Two", "element Three"};
const size_t SEEDED_STACK_ELEMENTS_SIZE = sizeof(SEEDED_STACK_ELEMENTS) / sizeof(SEEDED_STACK_ELEMENTS[0]);

/*
 * Declare setups
 */
SetupDeclare(EmptyStackSetup);
SetupDeclare(SeededStackSetup);

/*
 * Declare teardowns
 */
TeardownDeclare(StackTeardown);

/*
 * Declare fixtures
 */
FixtureDeclare(EmptyStackFixture);
FixtureDeclare(SeededStackFixture);

/*
 * Declare features
 */
FeatureDeclare(NewAndDelete);
FeatureDeclare(AddOneElement);
FeatureDeclare(AddTwoElements);
FeatureDeclare(AddThreeElements);
FeatureDeclare(DetectEmptiness);
FeatureDeclare(RemoveOneElement);
FeatureDeclare(RemoveTwoElements);
FeatureDeclare(RemoveAllElements);

/*
 * Describe our Subject
 */
Describe("stack_t",
         Trait(
                 "Ctor / Dtor",
                 Run(NewAndDelete, EmptyStackFixture)
         ),
         Trait(
                 "Add Elements",
                 Run(AddOneElement, EmptyStackFixture),
                 Run(AddTwoElements, EmptyStackFixture),
                 Run(AddThreeElements, EmptyStackFixture),
         ),
         Trait(
                 "Get Elements",
                 Run(DetectEmptiness, EmptyStackFixture)
         ),
         Trait(
                 "Remove Elements",
                 Run(RemoveOneElement, SeededStackFixture),
                 Run(RemoveTwoElements, SeededStackFixture),
                 Run(RemoveAllElements, SeededStackFixture),
         )
)

/*
 * Define setups
 */
SetupDefine(EmptyStackSetup) {
    stack_t sut = NULL;
    err_t err = stack_new(&sut);
    assert_equal(ERR_OK, err, "Expected: %d, got: %d\n", ERR_OK, err);
    assert_not_null(sut);
    return sut;
}

SetupDefine(SeededStackSetup) {
    stack_t sut = NULL;
    err_t err = stack_new(&sut);
    assert_equal(ERR_OK, err, "Expected: %d, got: %d\n", ERR_OK, err);
    assert_not_null(sut);
    for (size_t i = 0; i < SEEDED_STACK_ELEMENTS_SIZE; i++) {
        void *element = NULL;
        err = stack_add(sut, as(void *, SEEDED_STACK_ELEMENTS[i]));
        assert_equal(ERR_OK, err);
        err = stack_head(sut, &element);
        assert_equal(ERR_OK, err);
        assert_not_null(element);
        assert_equal(SEEDED_STACK_ELEMENTS[i], element);
        assert_string_equal(SEEDED_STACK_ELEMENTS[i], element);
    }
    return sut;
}

/*
 * Define teardowns
 */
TeardownDefine(StackTeardown) {
    stack_t sut = traits_context;
    assert_not_null(sut);
    err_t err = stack_delete(sut);
    assert_equal(ERR_OK, err, "Expected: %d, got: %d\n", ERR_OK, err);
}

/*
 * Define fixtures
 */
FixtureDefine(EmptyStackFixture, EmptyStackSetup, StackTeardown);
FixtureDefine(SeededStackFixture, SeededStackSetup, StackTeardown);

/*
 * Define features
 */
FeatureDefine(NewAndDelete) {
    (void) traits_context;
    /* Just run EmptyStackFixture */
}

FeatureDefine(AddOneElement) {
    err_t err;
    stack_t sut = traits_context;
    void *element = NULL;
    const char const *element_one = "Element One";

    err = stack_add(sut, as(void *, element_one));
    assert_equal(ERR_OK, err);
    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(element_one, element);
    assert_string_equal(element_one, element);
}

FeatureDefine(AddTwoElements) {
    err_t err;
    stack_t sut = traits_context;
    void *element = NULL;
    const char const *element_one = "Element One";
    const char const *element_two = "Element Two";

    err = stack_add(sut, as(void *, element_one));
    assert_equal(ERR_OK, err);
    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(element_one, element);
    assert_string_equal(element_one, element);

    err = stack_add(sut, as(void *, element_two));
    assert_equal(ERR_OK, err);
    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(element_two, element);
    assert_string_equal(element_two, element);
}

FeatureDefine(AddThreeElements) {
    err_t err;
    stack_t sut = traits_context;
    void *element = NULL;
    const char const *element_one = "Element One";
    const char const *element_two = "Element Two";
    const char const *element_three = "Element Three";

    err = stack_add(sut, as(void *, element_one));
    assert_equal(ERR_OK, err);
    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(element_one, element);
    assert_string_equal(element_one, element);

    err = stack_add(sut, as(void *, element_two));
    assert_equal(ERR_OK, err);
    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(element_two, element);
    assert_string_equal(element_two, element);

    err = stack_add(sut, as(void *, element_three));
    assert_equal(ERR_OK, err);
    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(element_three, element);
    assert_string_equal(element_three, element);
}

FeatureDefine(DetectEmptiness) {
    err_t err;
    stack_t sut = traits_context;
    void *element = NULL;

    err = stack_head(sut, &element);
    assert_equal(ERR_ACCESS, err);
}

FeatureDefine(RemoveOneElement) {
    err_t err;
    stack_t sut = traits_context;
    void *element = NULL;

    err = stack_remove(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 1], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 1], element);

    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);
}

FeatureDeclare(RemoveTwoElements) {
    err_t err;
    stack_t sut = traits_context;
    void *element = NULL;

    err = stack_remove(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 1], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 1], element);

    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);

    err = stack_remove(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);

    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 3], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 3], element);
}

FeatureDeclare(RemoveAllElements) {
    err_t err;
    stack_t sut = traits_context;
    void *element = NULL;

    err = stack_remove(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 1], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 1], element);

    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);

    err = stack_remove(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 2], element);

    err = stack_head(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 3], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 3], element);

    err = stack_remove(sut, &element);
    assert_equal(ERR_OK, err);
    assert_not_null(element);
    assert_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 3], element);
    assert_string_equal(SEEDED_STACK_ELEMENTS[SEEDED_STACK_ELEMENTS_SIZE - 3], element);

    err = stack_head(sut, &element);
    assert_equal(ERR_ACCESS, err);
}
