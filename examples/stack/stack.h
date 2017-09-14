/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   September 14, 2017 
 */

#ifndef __STACK_H__
#define __STACK_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stack *stack_t;

typedef enum err {
    ERR_OK,
    ERR_MEMORY,
    ERR_ACCESS,
} err_t;

extern err_t stack_new(stack_t *self_ref);
extern err_t stack_add(stack_t self, void *element);
extern err_t stack_head(stack_t self, void **element_ref);
extern err_t stack_remove(stack_t self, void **element_ref);
extern err_t stack_delete(stack_t self);

#ifdef __cplusplus
}
#endif

#endif /* __STACK_H__ */
