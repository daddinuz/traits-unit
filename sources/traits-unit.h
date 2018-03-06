/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   March 06, 2018
 */

#include <stddef.h>
#include <setjmp.h>
#include <signal.h>


#ifndef TRAITS_UNIT_INCLUDED
#define TRAITS_UNIT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* [public section begin] */

/*
 * Versioning
 */
#define TRAITS_UNIT_VERSION_MAJOR       0
#define TRAITS_UNIT_VERSION_MINOR       2
#define TRAITS_UNIT_VERSION_PATCH       0
#define TRAITS_UNIT_VERSION_SUFFIX      "rc"
#define TRAITS_UNIT_VERSION_IS_RELEASE  0
#define TRAITS_UNIT_VERSION_HEX         0x000200

/*
 * Constants
 */
#define TRAITS_UNIT_MAX_TRAITS          (32 + 1)
#define TRAITS_UNIT_MAX_FEATURES        (128 + 1)

/*
 * Types
 */
typedef void *traits_unit_setup_fn(void);
typedef void traits_unit_teardown_fn(void);

typedef struct traits_unit_fixture_t {
    traits_unit_setup_fn *setup;
    traits_unit_teardown_fn *teardown;
} traits_unit_fixture_t;

typedef void traits_unit_feature_fn(void);

typedef enum traits_unit_action_t {
    TRAITS_UNIT_ACTION_RUN,
    TRAITS_UNIT_ACTION_SKIP,
    TRAITS_UNIT_ACTION_TODO
} traits_unit_action_t;

typedef struct traits_unit_feature_t {
    traits_unit_action_t action;
    const char *feature_name;
    traits_unit_fixture_t *fixture;
    traits_unit_feature_fn *feature;
} traits_unit_feature_t;

typedef struct traits_unit_trait_t {
    const char *trait_name;
    traits_unit_feature_t features[TRAITS_UNIT_MAX_FEATURES];
} traits_unit_trait_t;

typedef struct traits_unit_subject_t {
    const char *subject;
    traits_unit_trait_t traits[TRAITS_UNIT_MAX_TRAITS];
} traits_unit_subject_t;

/*
 * Functions
 */
extern const char *
traits_unit_version(void);

extern void *
traits_unit_get_context(void);

extern size_t
traits_unit_get_handled_signals_counter(void);

/*
 * Declare main in order to force definition by traits-unit
 */
extern int
main(int argc, char *argv[]);

/*
 * Macros
 */
#define SetupDeclare(Name)                      \
    extern void *__TRAITS_UNIT_SETUP_ID(Name)(void) // NOLINT

#define SetupDefine(Name)                       \
    void *__TRAITS_UNIT_SETUP_ID(Name)(void)        // NOLINT

#define TeardownDeclare(Name)                   \
    extern void __TRAITS_UNIT_TEARDOWN_ID(Name)(void)

#define TeardownDefine(Name)                    \
    void __TRAITS_UNIT_TEARDOWN_ID(Name)(void)

#define FixtureDeclare(Name)                    \
    extern traits_unit_fixture_t __TRAITS_UNIT_FIXTURE_ID(Name)

#define FixtureDefine(Name, Setup, Teardown)    \
    traits_unit_fixture_t __TRAITS_UNIT_FIXTURE_ID(Name) = {.setup=__TRAITS_UNIT_SETUP_ID(Setup), .teardown=__TRAITS_UNIT_TEARDOWN_ID(Teardown)}

#define FeatureDeclare(Name)                    \
    extern void __TRAITS_UNIT_FEATURE_ID(Name)(void)

#define FeatureDefine(Name)                     \
    void __TRAITS_UNIT_FEATURE_ID(Name)(void)

#define Describe(Subject, ...)                  \
    traits_unit_subject_t traits_unit_subject = {.subject=(Subject), .traits={__VA_ARGS__}};

#define Trait(Name, ...)                        \
    {.trait_name=(Name), .features={__VA_ARGS__}}

#define Run(...)                                \
    __TRAITS_UNIT_FEATURE_RUN(__VA_ARGS__, __TraitsUnitDefaultFixture, __TraitsUnitDefaultFixture)

#define Skip(...)                               \
    __TRAITS_UNIT_FEATURE_SKIP(__VA_ARGS__, __TraitsUnitDefaultFixture, __TraitsUnitDefaultFixture)

#define Todo(...)                               \
    __TRAITS_UNIT_FEATURE_TODO(__VA_ARGS__, __TraitsUnitDefaultFixture, __TraitsUnitDefaultFixture)

/*
 * Helper macro to handle signals
 */
#define traits_unit_with_raises(xSignal)                                                            \
    for (                                                                                           \
        __traits_unit_previous_signal_handler = signal((xSignal), __traits_unit_signal_handler);    \
        !sigsetjmp(__traits_unit_jump_buffer, true);                                                \
    )

/* [public section end] */

/* [private section begin] */

#define __TRAITS_UNIT_CAT_IMPL_(x, ...)      x ## __VA_ARGS__
#define __TRAITS_UNIT_CAT(x, ...)           __TRAITS_UNIT_CAT_IMPL_(x, __VA_ARGS__)

#define __TRAITS_UNIT_TO_STRING_IMPL_(x)     #x
#define __TRAITS_UNIT_TO_STRING(x)          __TRAITS_UNIT_TO_STRING_IMPL_(x)

#define __TRAITS_UNIT_SETUP_ID(Name)        __TRAITS_UNIT_CAT(traits_unit_user_setup_, Name)
#define __TRAITS_UNIT_TEARDOWN_ID(Name)     __TRAITS_UNIT_CAT(traits_unit_user_teardown_, Name)
#define __TRAITS_UNIT_FIXTURE_ID(Name)      __TRAITS_UNIT_CAT(traits_unit_user_fixture_, Name)
#define __TRAITS_UNIT_FEATURE_ID(Name)      __TRAITS_UNIT_CAT(traits_unit_user_feature_, Name)

#define __TRAITS_UNIT_FEATURE_RUN(Name, Fixture, ...)               \
    {.feature_name=__TRAITS_UNIT_TO_STRING(Name), .feature=__TRAITS_UNIT_FEATURE_ID(Name), .fixture=&__TRAITS_UNIT_FIXTURE_ID(Fixture), .action=TRAITS_UNIT_ACTION_RUN}

#define __TRAITS_UNIT_FEATURE_SKIP(Name, Fixture, ...)              \
    {.feature_name=__TRAITS_UNIT_TO_STRING(Name), .feature=__TRAITS_UNIT_FEATURE_ID(Name), .fixture=&__TRAITS_UNIT_FIXTURE_ID(Fixture), .action=TRAITS_UNIT_ACTION_SKIP}

#define __TRAITS_UNIT_FEATURE_TODO(Name, Fixture, ...)              \
    {.feature_name=__TRAITS_UNIT_TO_STRING(Name), .feature=__TRAITS_UNIT_FEATURE_ID(Name), .fixture=&__TRAITS_UNIT_FIXTURE_ID(Fixture), .action=TRAITS_UNIT_ACTION_TODO}

extern jmp_buf __traits_unit_jump_buffer;
extern void (*volatile __traits_unit_previous_signal_handler)(int);

extern void
__traits_unit_signal_handler(int signal_id);

SetupDeclare(__TraitsUnitDefaultSetup);
TeardownDeclare(__TraitsUnitDefaultTeardown);
FixtureDeclare(__TraitsUnitDefaultFixture);

/* [private section end] */

#ifdef __cplusplus
}
#endif

#endif /* TRAITS_UNIT_INCLUDED */
