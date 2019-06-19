/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Dan Halbert for Adafruit Industries
 * Copyright (c) 2018 Artur Pacholec
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

#ifndef MICROPY_INCLUDED_SHARED_BINDINGS_BLEIO_SERVICE_H
#define MICROPY_INCLUDED_SHARED_BINDINGS_BLEIO_SERVICE_H

#include "common-hal/bleio/Service.h"

const mp_obj_type_t bleio_service_type;

extern void common_hal_bleio_service_construct(bleio_service_obj_t *self, bleio_uuid_obj_t *uuid, mp_obj_list_t *characteristic_list, bool is_secondary);
extern bleio_uuid_obj_t *common_hal_bleio_service_get_uuid(bleio_service_obj_t *self);
extern mp_obj_list_t *common_hal_bleio_service_get_characteristic_list(bleio_service_obj_t *self);
extern bool common_hal_bleio_service_get_is_secondary(bleio_service_obj_t *self);
extern void common_hal_bleio_service_set_device(bleio_service_obj_t *self, mp_obj_t device);
extern void common_hal_bleio_service_add_all_characteristics(bleio_service_obj_t *self);

#endif // MICROPY_INCLUDED_SHARED_BINDINGS_BLEIO_SERVICE_H
