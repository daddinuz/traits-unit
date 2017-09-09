/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 02, 2017 
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "traits-unit.h"

#if defined(__GNUC__) || defined(__clang__)
#   define TRAITS_UNIT_ATTRIBUTE_FORMAT(x, y)           __attribute__((__format__(__printf__, x, y)))
#   define TRAITS_UNIT_ATTRIBUTE_FORMAT_NORETURN(x, y)  __attribute__((__format__(__printf__, x, y), __noreturn__))
#else
#   define TRAITS_UNIT_ATTRIBUTE_FORMAT(x, y)
#   define TRAITS_UNIT_ATTRIBUTE_FORMAT_NORETURN(x, y)
#endif

/*
 * Some constants
 */
#define TRAITS_UNIT_OUTPUT_STREAM                       stdout
#define TRAITS_UNIT_BUFFER_CAPACITY                     (2 << 8)
#define TRAITS_UNIT_INDENTATION_STEP                    2

/*
 * Forward declare traits subject (this should come from the test file)
 */
extern traits_unit_subject_t traits_unit_subject;

/*
 * Implements default fixtures from header file
 */
SetupDefine(DefaultSetup) {
    printf(" <DefaultSetup> ");
    return NULL;
}

TeardownDefine(DefaultTeardown) {
    (void) traits_context;
    printf(" <DefaultTeardown> ");
}

FixtureDefine(DefaultFixture, DefaultSetup, DefaultTeardown);

/*
 * Internal declarations
 */
static void *traits_unit_shared_malloc(size_t size);
static void traits_unit_shared_free(void *address, size_t size);

typedef struct traits_unit_buffer_t {
    size_t _index;
    size_t _capacity;
    char *_content;
} traits_unit_buffer_t;

static traits_unit_buffer_t *traits_unit_buffer_new(size_t capacity);

static void traits_unit_buffer_read(traits_unit_buffer_t *buffer, int fd);

static char *traits_unit_buffer_get(traits_unit_buffer_t *buffer);

static void traits_unit_buffer_clear(traits_unit_buffer_t *buffer);

static void traits_unit_buffer_delete(traits_unit_buffer_t **buffer);

static void _traits_unit_panic(size_t line, const char *file, const char *fmt, ...)
TRAITS_UNIT_ATTRIBUTE_FORMAT_NORETURN(3, 4);

static void traits_unit_print(size_t indent, const char *fmt, ...)
TRAITS_UNIT_ATTRIBUTE_FORMAT(2, 3);

static int traits_unit_run_feature(traits_unit_feature_t *feature, traits_unit_buffer_t *buffer);

/*
 * Macro helpers
 */
#define traits_unit_panic(fmt, ...)                 _traits_unit_panic(__LINE__, __FILE__, fmt, __VA_ARGS__)
#define traits_unit_newline()                       traits_unit_print(0, "\n")

/*
 * Implements main
 */
int main(int argc, char *argv[]) {
    (void) argc, (void) argv;
    size_t indentation_level = 0;
    traits_unit_trait_t *trait = NULL;
    traits_unit_feature_t *feature = NULL;
    traits_unit_buffer_t *buffer = traits_unit_buffer_new(TRAITS_UNIT_BUFFER_CAPACITY);
    size_t counter_succeed = 0, counter_skipped = 0, counter_failed = 0, counter_todo = 0, counter_all = 0;

    traits_unit_print(indentation_level, "Describing: %s\n", traits_unit_subject.subject);
    indentation_level += TRAITS_UNIT_INDENTATION_STEP;
    for (size_t i = 0; (trait = &traits_unit_subject.traits[i]) && trait->trait_name && trait->features; i++) {
        traits_unit_print(indentation_level, "Trait: %s\n", traits_unit_subject.traits[i].trait_name);
        indentation_level += TRAITS_UNIT_INDENTATION_STEP;
        for (size_t x = 0; (feature = &trait->features[x]) && feature->feature && feature->feature_name; x++) {
            counter_all++;
            traits_unit_print(indentation_level, "Feature: %s... ", feature->feature_name);
            if (feature->action == TRAITS_UNIT_ACTION_RUN) {
                traits_unit_buffer_clear(buffer);
                if (traits_unit_run_feature(feature, buffer) == EXIT_SUCCESS) {
                    counter_succeed++;
                    traits_unit_print(0, "succeed\n");
                } else {
                    counter_failed++;
                    traits_unit_print(0, "failed\n\n%s\n", traits_unit_buffer_get(buffer));
                }
            } else if (feature->action == TRAITS_UNIT_ACTION_SKIP) {
                counter_skipped++;
                traits_unit_print(0, "skipped\n");
            } else if (feature->action == TRAITS_UNIT_ACTION_TODO) {
                counter_todo++;
                traits_unit_print(0, "todo\n");
            } else {
                traits_unit_panic("Unexpected traits_unit_action_t value: %d\n", feature->action);
            }
        }
        indentation_level -= TRAITS_UNIT_INDENTATION_STEP;
    }
    indentation_level -= TRAITS_UNIT_INDENTATION_STEP;
    traits_unit_newline();
    traits_unit_print(indentation_level, "Succeed: %zu\n", counter_succeed);
    traits_unit_print(indentation_level, "Skipped: %zu\n", counter_skipped);
    traits_unit_print(indentation_level, " Failed: %zu\n", counter_failed);
    traits_unit_print(indentation_level, "   Todo: %zu\n", counter_todo);
    traits_unit_print(indentation_level, "    All: %zu\n", counter_all);

    traits_unit_buffer_delete(&buffer);
    return (counter_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
 * Internal implementations
 */
void *traits_unit_shared_malloc(size_t size) {
    /* Our memory will be readable and writable */
    int protection = PROT_READ | PROT_WRITE;

    /*
     * The buffer will be shared (meaning other processes can access it), but
     * anonymous (meaning third-party processes cannot obtain an address for it),
     * so only this process and its children will be able to use it.
     */
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    /* Perform memory mapping */
    void *memory = mmap(NULL, size, protection, visibility, 0, 0);
    if (!memory) {
        traits_unit_panic("%s\n", "Unable to map memory");
    }

    return memory;
}

void traits_unit_shared_free(void *address, size_t size) {
    if (0 != munmap(address, size)) {
        traits_unit_panic("%s\n", "Unable to unmap memory");
    }
}

traits_unit_buffer_t *traits_unit_buffer_new(size_t capacity) {
    traits_unit_buffer_t *self = traits_unit_shared_malloc(sizeof(*self));
    if (!self) {
        traits_unit_panic("%s\n", "Out of memory.");
    }
    self->_content = traits_unit_shared_malloc(capacity + 1);
    if (!self->_content) {
        traits_unit_panic("%s\n", "Out of memory.");
    }
    self->_index = 0;
    self->_capacity = capacity;
    self->_content[capacity] = 0;
    return self;
}

void traits_unit_buffer_read(traits_unit_buffer_t *buffer, int fd) {
    assert(buffer);
    FILE *stream = fdopen(fd, "r");

    /* Open fd */
    if (!stream) {
        traits_unit_panic("%s\n", "Unable to open file.");
    }

    /* Read from fd and write to buffer */
    buffer->_index += fread(
            buffer->_content + buffer->_index,
            sizeof(buffer->_content[0]),
            buffer->_capacity - buffer->_index,
            stream
    );

    /* Close the stream */
    fclose(stream);
}

char *traits_unit_buffer_get(traits_unit_buffer_t *buffer) {
    assert(buffer);
    return buffer->_content;
}

void traits_unit_buffer_clear(traits_unit_buffer_t *buffer) {
    assert(buffer);
    buffer->_index = 0;
    buffer->_content[0] = 0;
}

void traits_unit_buffer_delete(traits_unit_buffer_t **buffer) {
    assert(buffer && *buffer);
    traits_unit_shared_free((*buffer)->_content, (*buffer)->_capacity + 1);
    traits_unit_shared_free(*buffer, sizeof(*buffer));
    *buffer = NULL;
}

void _traits_unit_panic(size_t line, const char *file, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "\nAt %s:%zu\nError: %s\n", file, line, strerror(errno));
    vfprintf(stderr, fmt, args);
    fputs("", stderr);
    va_end(args);
    exit(-1);
}

void traits_unit_print(size_t indent, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(TRAITS_UNIT_OUTPUT_STREAM, "%*s", (int) indent, "");
    vfprintf(TRAITS_UNIT_OUTPUT_STREAM, fmt, args);
    va_end(args);
}

int traits_unit_run_feature(traits_unit_feature_t *feature, traits_unit_buffer_t *buffer) {
    pid_t pid;
    int fd, pipe_fd[2], pid_status;

    /* Flush TRAITS_UNIT_OUTPUT_STREAM */
    fflush(TRAITS_UNIT_OUTPUT_STREAM);

    /* Open a pipe */
    if (pipe(pipe_fd) < 0) {
        traits_unit_panic("%s\n", "Unable to open pipe.");
    }

    /* Fork the process */
    if ((pid = fork()) < 0) {
        traits_unit_panic("%s\n", "Unable to fork process.");
    }

    /* We are in the child process */
    if (pid == 0) {
        /* Close read end of pipe */
        close(pipe_fd[0]);

        /* Get write end of pipe */
        fd = pipe_fd[1];

        /* Redirect STDERR to pipe*/
        dup2(fd, STDERR_FILENO);

        /* Setup context */
        void *context = feature->fixture->setup();

        /* Run feature */
        feature->feature(context);

        /* Teardown context */
        feature->fixture->teardown(context);

        /* Close fd */
        close(fd);

        /* Exit normally */
        exit(EXIT_SUCCESS);
    }

    /* We are in the parent process */

    /* Wait for children */
    wait(&pid_status);

    /* Close write end of pipe */
    close(pipe_fd[1]);

    /* Get read end of pipe */
    fd = pipe_fd[0];

    /* Redirect the children output to the global buffer */
    traits_unit_buffer_read(buffer, fd);

    /* Close fd */
    close(fd);

    /* Flush TRAITS_UNIT_OUTPUT_STREAM */
    fflush(TRAITS_UNIT_OUTPUT_STREAM);
    return pid_status;
}
