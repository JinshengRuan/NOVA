/*
 * Virtual-Machine Identifier (VMID)
 *
 * Copyright (C) 2019-2020 Udo Steinberg, BedRock Systems, Inc.
 *
 * This file is part of the NOVA microhypervisor.
 *
 * NOVA is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * NOVA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 */

#pragma once

#include "types.hpp"

class Vmid
{
    private:
        uint16 val;

        static Vmid allocator;

        inline Vmid (uint16 v) : val (v) {}

        // FIXME: Handle overflow
        static inline uint16 allocate()
        {
            return __atomic_add_fetch (&allocator.val, 1, __ATOMIC_SEQ_CST);
        }

    public:
        inline Vmid() : val (allocate()) {}

        mword vmid() const { return val & 0xff; }
};
