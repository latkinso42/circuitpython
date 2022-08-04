/*
 * This file is an implementation of the generailized Fibonacci in C for
 * CircuitPython. Taken from on PulseIO.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 Lee Atkinson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdint.h>

#include "shared/runtime/context_manager_helpers.h"
#include "py/objproperty.h"
#include "py/runtime.h"
#include "py/runtime0.h"
#include "shared-bindings/fibonacci/Fibonacci.h"
#include "shared-bindings/util.h"
#include "supervisor/shared/translate/translate.h"

//| class Fibonacci:
//|     """Compute a series of sequential numbers based on previous two inputs.
///        Instance creates initial spacing and progression track."""
//|
//|     def __init__(self, a: int = 0, b: int = 1) -> None:
///
//|         Create a Fibonacci object associated with two starting numbers. The object acts as
//|         a read-only sequence initial pair of numbers by which to begin the generalized
///         Fibonacci sequence.
//|
//|         :param int a:
//|         :param int b:
//|
//|         Generate a series of N fibonacci ::
//|
//|           import fibonacci
///
//|           fib = fibonacci.Fibonacci(a,b)
///
///           fib.generate(N)
//|
//|           # Clear the initial number and go to the default a=0, b=1
///
//|           fib.clear()
//|
STATIC mp_obj_t fibonacci_fibonacci_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    enum { ARG_a, ARG_b };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_a, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_b, MP_ARG_INT, {.u_int = 0} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    fibonacci_fibonacci_obj_t *self = m_new_obj(fibonacci_fibonacci_obj_t);
    self->base.type = &fibonacci_fibonacci_type;

    common_hal_fibonacci_fibonacci_construct(self, args[ARG_a].u_int, args[ARG_b].u_int);

    return MP_OBJ_FROM_PTR(self);
}

//|     def deinit(self) -> None:
//|         """Deinitialises the Fibonacci and releases any hardware resources for reuse."""
//|         ...
//|
STATIC mp_obj_t fibonacci_fibonacci_deinit(mp_obj_t self_in) {
    fibonacci_fibonacci_obj_t *self = MP_OBJ_TO_PTR(self_in);
    common_hal_fibonacci_fibonacci_deinit(self);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(fibonacci_fibonacci_deinit_obj, fibonacci_fibonacci_deinit);

STATIC void check_for_deinit(fibonacci_fibonacci_obj_t *self) {
    if (common_hal_fibonacci_fibonacci_deinited(self)) {
        raise_deinited_error();
    }
}

//|     def __enter__(self) -> Fibonacci:
//|         """No-op used by Context Managers."""
//|         ...
//|
//  Provided by context manager helper.

//|     def __exit__(self) -> None:
//|         """Automatically deinitializes the hardware when exiting a context. See
//|         :ref:`lifetime-and-contextmanagers` for more info."""
//|         ...
//|
STATIC mp_obj_t fibonacci_fibonacci_obj___exit__(size_t n_args, const mp_obj_t *args) {
    (void)n_args;
    common_hal_fibonacci_fibonacci_deinit(args[0]);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(fibonacci_fibonacci___exit___obj, 4, 4, fibonacci_fibonacci_obj___exit__);


//|     def clear(self) -> None:
//|         """Clears all set data"""
//|         ...
//|
STATIC mp_obj_t fibonacci_fibonacci_obj_clear(mp_obj_t self_in) {
    fibonacci_fibonacci_obj_t *self = MP_OBJ_TO_PTR(self_in);
    check_for_deinit(self);

    common_hal_fibonacci_fibonacci_clear(self);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(fibonacci_fibonacci_clear_obj, fibonacci_fibonacci_obj_clear);

//|     generate: int
//|     """Generates N numbers in sequesnce and returns the last one generated."""
//
STATIC mp_obj_t fibonacci_fibonacci_obj_generate
    (size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_N };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_N, MP_ARG_INT, {.u_int = 0} },
    };
    fibonacci_fibonacci_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    check_for_deinit(self);

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    uint16_t N = common_hal_fibonacci_fibonacci_generate(self, args[ARG_N].u_int);

    return MP_OBJ_NEW_SMALL_INT(N);
}
MP_DEFINE_CONST_FUN_OBJ_KW(fibonacci_fibonacci_generate_obj, 1, fibonacci_fibonacci_obj_generate);


///----------------------------------
//|     a: uint16_t
//|     """The first number of the Fibonacci Generator."""
//|
STATIC mp_obj_t fibonacci_fibonacci_obj_get_a(mp_obj_t self_in) {
    fibonacci_fibonacci_obj_t *self = MP_OBJ_TO_PTR(self_in);
    check_for_deinit(self);
    return MP_OBJ_NEW_SMALL_INT(common_hal_fibonacci_fibonacci_get_a(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(fibonacci_fibonacci_get_a_obj, fibonacci_fibonacci_obj_get_a);
// MP_PROPERTY_GETTER(fibonacci_fibonacci_a_obj,(mp_obj_t)&fibonacci_fibonacci_get_a_obj);

STATIC mp_obj_t fibonacci_fibonacci_obj_set_a(mp_obj_t self_in, mp_obj_t a_value) {
    fibonacci_fibonacci_obj_t *self = MP_OBJ_TO_PTR(self_in);
    check_for_deinit(self);
    // uint16_t a =

    common_hal_fibonacci_fibonacci_set_a(self, mp_obj_is_small_int(a_value));
    // MP_OBJ_NEW_SMALL_INT(a));
    // return MP_OBJ_NEW_SMALL_INT(a);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(fibonacci_fibonacci_set_a_obj, fibonacci_fibonacci_obj_set_a);
MP_PROPERTY_GETSET(fibonacci_fibonacci_a_obj,
    (mp_obj_t)&fibonacci_fibonacci_get_a_obj,
    (mp_obj_t)&fibonacci_fibonacci_set_a_obj);
















///----------------------------------
//|     b: uint16_t
//|     """The second number of the Fibonacci Generator."""
//|
STATIC mp_obj_t fibonacci_fibonacci_obj_get_b(mp_obj_t self_in) {
    fibonacci_fibonacci_obj_t *self = MP_OBJ_TO_PTR(self_in);
    check_for_deinit(self);

    return MP_OBJ_NEW_SMALL_INT(common_hal_fibonacci_fibonacci_get_b(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(fibonacci_fibonacci_get_b_obj, fibonacci_fibonacci_obj_get_b);

MP_PROPERTY_GETTER(fibonacci_fibonacci_b_obj,
    (mp_obj_t)&fibonacci_fibonacci_get_b_obj);


///----------------------------------
//|     timeout: uint16_t
//|     """The timeout of the Fibonacci Generator."""
//|
/*
STATIC mp_obj_t fibonacci_fibonacci_obj_get_timeout(mp_obj_t self_in) {
    fibonacci_fibonacci_obj_t *self = MP_OBJ_TO_PTR(self_in);
    check_for_deinit(self);

    return MP_OBJ_NEW_SMALL_INT(common_hal_fibonacci_fibonacci_get_timeout(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(fibonacci_fibonacci_get_timeout_obj, fibonacci_fibonacci_obj_get_timeout);

MP_PROPERTY_GETTER(fibonacci_fibonacci_timeout_obj,
    (mp_obj_t)&fibonacci_fibonacci_get_timeout_obj);
*/






///-----------------------
STATIC const mp_rom_map_elem_t fibonacci_fibonacci_locals_dict_table[] = {
    // Methods
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&fibonacci_fibonacci_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&fibonacci_fibonacci___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_clear), MP_ROM_PTR(&fibonacci_fibonacci_clear_obj) },
    { MP_ROM_QSTR(MP_QSTR_generate), MP_ROM_PTR(&fibonacci_fibonacci_generate_obj) },

    // Properties
    { MP_ROM_QSTR(MP_QSTR_a), MP_ROM_PTR(&fibonacci_fibonacci_a_obj) },
    { MP_ROM_QSTR(MP_QSTR_b), MP_ROM_PTR(&fibonacci_fibonacci_b_obj) },
    // { MP_ROM_QSTR(MP_QSTR_timeout), MP_ROM_PTR(&fibonacci_fibonacci_timeout_obj) },
};

STATIC MP_DEFINE_CONST_DICT(fibonacci_fibonacci_locals_dict, fibonacci_fibonacci_locals_dict_table);

const mp_obj_type_t fibonacci_fibonacci_type = {
    { &mp_type_type },
    .flags = MP_TYPE_FLAG_EXTENDED,
    .name = MP_QSTR_Fibonacci,
    .make_new = fibonacci_fibonacci_make_new,
    .locals_dict = (mp_obj_dict_t *)&fibonacci_fibonacci_locals_dict,
    //    MP_TYPE_EXTENDED_FIELDS(
    //    .subscr = fibonacci_subscr,
    //    .unary_op = fibonacci_unary_op,
    //    ),
};
