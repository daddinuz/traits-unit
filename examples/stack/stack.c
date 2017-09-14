/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 14, 2017 
 */

#include <stdlib.h>
#include <assert.h>
#include "stack.h"

/*
 * Node
 */
typedef struct node {
    void *element;
    struct node *next;
} *node_t;

static err_t node_new(node_t *self_ref, void *element) {
    assert(self_ref);
    err_t err;
    node_t self = calloc(1, sizeof(*self));
    if (self) {
        self->element = element;
        *self_ref = self;
        err = ERR_OK;
    } else {
        err = ERR_MEMORY;
    }
    return err;
}

static err_t node_delete(node_t self, void **element_ref) {
    assert(self);
    if (element_ref) {
        *element_ref = self->element;
    }
    free(self);
    return ERR_OK;
}

/*
 * Stack
 */
struct stack {
    node_t head;
};

err_t stack_new(stack_t *self_ref) {
    assert(self_ref);
    err_t err;
    stack_t self = calloc(1, sizeof(*self));
    if (self) {
        self->head = NULL;
        *self_ref = self;
        err = ERR_OK;
    } else {
        err = ERR_MEMORY;
    }
    return err;
}

err_t stack_add(stack_t self, void *element) {
    assert(self);
    node_t node = NULL;
    err_t err = node_new(&node, element);
    if (ERR_OK == err) {
        node->next = self->head;
        self->head = node;
    }
    return err;
}

err_t stack_head(stack_t self, void **element_ref) {
    assert(self);
    assert(element_ref);
    err_t err;
    if (self->head) {
        *element_ref = self->head->element;
        err = ERR_OK;
    } else {
        err = ERR_ACCESS;
    }
    return err;
}

err_t stack_remove(stack_t self, void **element_ref) {
    assert(self);
    assert(element_ref);
    err_t err;
    if (self->head) {
        node_t next = self->head->next;
        err = node_delete(self->head, element_ref);
        if (ERR_OK == err) {
            self->head = next;
        }
    } else {
        err = ERR_ACCESS;
    }
    return err;
}

err_t stack_delete(stack_t self) {
    assert(self);
    err_t err = ERR_OK;
    node_t head = self->head, next;
    while (head) {
        next = head->next;
        err = node_delete(head, NULL);
        if (ERR_OK != err) {
            break;
        }
        head = next;
    }
    return err;
}
