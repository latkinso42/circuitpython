/*
 * This file is an implementation of the generailized Fibonacci in C for CircuitPython. Taken from on PulseIO.
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
#include "py/runtime.h"
#include "supervisor/shared/translate/translate.h"
#include "shared-bindings/fibonacci/Fibonacci.h"
#include "common-hal/fibonacci/Fibonacci.h"

void common_hal_fibonacci_fibonacci_construct(fibonacci_fibonacci_obj_t *self, uint16_t a, uint16_t b) {
    self->a = a;
    self->b = b;
    self->timeout = 10;
    // somewhere need to enforce a<b
    // somewhere need to establish default timeout
}

bool common_hal_fibonacci_fibonacci_deinited(fibonacci_fibonacci_obj_t *self) {
    return 0;
}

void common_hal_fibonacci_fibonacci_deinit(fibonacci_fibonacci_obj_t *self) {
    if (common_hal_fibonacci_fibonacci_deinited(self)) {
        return;
    }
}


void common_hal_fibonacci_fibonacci_clear(fibonacci_fibonacci_obj_t *self) {
    self->a = 42;
    self->b = 42;
    self->timeout = 42;
    return;
}

uint16_t common_hal_fibonacci_fibonacci_generate(fibonacci_fibonacci_obj_t *self, uint16_t N) {

    uint16_t aa = self->a;
    uint16_t bb = self->b;
    uint16_t cc, i;

    if (N == 0) {
        return aa;
    }

    for (i = 2; i <= N; i++) {
        cc = aa + bb;
        aa = bb;
        bb = cc;
    }

    return bb;
}


uint16_t common_hal_fibonacci_fibonacci_get_a(fibonacci_fibonacci_obj_t *self) {
    return self->a;
}

uint16_t common_hal_fibonacci_fibonacci_get_b(fibonacci_fibonacci_obj_t *self) {
    return self->b;
}

uint16_t common_hal_fibonacci_fibonacci_get_timeout(fibonacci_fibonacci_obj_t *self) {
    return self->timeout;
}

uint16_t common_hal_fibonacci_fibonacci_set_a(fibonacci_fibonacci_obj_t *self, uint16_t a) {
    return self->a = a;
}

/*
uint16_t common_hal_fibonacci_fibonacci_b(fibonacci_fibonacci_obj_t *self, uint16_t b) {
  return self->b = b;
}

uint16_t common_hal_fibonacci_fibonacci_set_timeout(fibonacci_fibonacci_obj_t *self, uint16_t timeout) {
  return self->timeout = timeout;
}
*/
