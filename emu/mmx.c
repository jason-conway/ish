//
//  mmx.c
//  libISH_emu
//
//  Created by Jason Conway on 02/02/23.
//

#include <math.h>
#include <string.h>

#include "emu/vec.h"
#include "emu/cpu.h"

union vec { 
    uint64_t qw;
    uint8_t u8[8];
    uint16_t u16[4];
};

void vec_and64(NO_CPU, union mm_reg *src, union mm_reg *dst) {
    dst->qw &= src->qw;
}
void vec_or64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    dst->qw |= src->qw;
}
void vec_xor64(NO_CPU, union mm_reg *src, union mm_reg *dst) {
    dst->qw ^= src->qw;
}
void vec_add_q64(NO_CPU, union mm_reg *src, union mm_reg *dst) {
    dst->qw += src->qw;
}
void vec_unpackl_dq64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    dst->dw[1] = src->dw[0];
}

void vec_shiftl_w64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    if (src->qw > 15) {
        dst->qw = 0;
    } else {
        union vec d = { .qw = dst->qw};
        for (unsigned i = 0; i < array_size(d.u16); i++)
            d.u16[i] <<= src->qw;
        dst->qw = d.qw;
    }
}
void vec_shiftl_d64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    if (src->qw > 31) {
        dst->qw = 0;
    } else {
        dst->dw[0] <<= src->qw;
        dst->dw[1] <<= src->qw;
    }
}
void vec_shiftl_q64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    if (src->qw > 63)
        dst->qw = 0;
    else
        dst->qw <<= src->qw;
}

void vec_shiftr_w64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    if (src->qw > 15) {
        dst->qw = 0;
    } else {
        union vec d = { .qw = dst->qw};
        for (unsigned i = 0; i < array_size(d.u16); i++)
            d.u16[i] >>= src->qw;
        dst->qw = d.qw;
    }
}
void vec_shiftr_d64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    if (src->qw > 31) {
        dst->qw = 0;
    } else {
        dst->dw[0] >>= src->qw;
        dst->dw[1] >>= src->qw;
    }
}
void vec_shiftr_q64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    if (src->qw > 63)
        dst->qw = 0;
    else
        dst->qw >>= src->qw;
}

void vec_imm_shiftl_q64(NO_CPU, const uint8_t amount, union mm_reg *dst) {
    if (amount > 63)
        dst->qw = 0;
    else
        dst->qw <<= amount;
}
void vec_imm_shiftr_q64(NO_CPU, const uint8_t amount, union mm_reg *dst) {
    if (amount > 63)
        dst->qw = 0;
    else
        dst->qw >>= amount;
}

void vec_shuffle_w64(NO_CPU, const union mm_reg *src, union mm_reg *dst, uint8_t encoding) {
    union vec s = { .qw = src->qw}, d = { .qw = dst->qw };
    for (unsigned i = 0; i < 4; i++)
        d.u16[i] = s.u16[(encoding >> (2 * i)) % 4];
    dst->qw = d.qw;
}

void vec_compares_gtb64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    union vec s = { .qw = src->qw}, d = { .qw = dst->qw };
    for (unsigned i = 0; i < array_size(s.u8); i++)
        d.u8[i] = (int8_t)d.u8[i] > (int8_t)s.u8[i] ? ~0 : 0;
    dst->qw = d.qw;
}
void vec_compare_eqb64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    union vec s = { .qw = src->qw}, d = { .qw = dst->qw };
    for (unsigned i = 0; i < array_size(s.u8); i++)
        d.u8[i] = d.u8[i] == s.u8[i] ? ~0 : 0;
    dst->qw = d.qw;
}

void vec_compare_eqw64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    union vec s = { .qw = src->qw}, d = { .qw = dst->qw };
    for (unsigned i = 0; i < array_size(s.u16); i++)
        d.u16[i] = d.u16[i] == s.u16[i] ? ~0 : 0;
    dst->qw = d.qw;
}

void vec_add_b64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    union vec s = { .qw = src->qw}, d = { .qw = dst->qw };
    for (unsigned i = 0; i < array_size(s.u8); i++)
        d.u8[i] += s.u8[i];
    dst->qw = d.qw;
}

void vec_mulu64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    union vec s = { .qw = src->qw}, d = { .qw = dst->qw };
    for (unsigned i = 0; i < 4; i++) {
        uint32_t res = ((int16_t)d.u16[i] * (int16_t)s.u16[i]);
        d.u16[i] = ((res >> 16) & 0xffff);
    }
    dst->qw = d.qw;
}
void vec_mull64(NO_CPU, const union mm_reg *src, union mm_reg *dst) {
    union vec s = { .qw = src->qw}, d = { .qw = dst->qw };
    for (int i = 0; i < 4; i++) {
        d.u16[i] = (uint16_t)(d.u16[i] * s.u16[i]);
    }
    dst->qw = d.qw;
}
void vec_mulu_dq64(NO_CPU, union mm_reg *src, union mm_reg *dst) {
    dst->qw = (uint64_t) src->dw[0] * dst->dw[0];
}

void vec_movmask_b64(NO_CPU, const union mm_reg *src, uint32_t *dst) {
    union vec s = { .qw = src->qw};
    *dst = 0;
    for (unsigned i = 0; i < array_size(s.u8); i++) {
        if (s.u8[i] & (1 << 7))
            *dst |= 1 << i;
    }
}

void vec_insert_w64(NO_CPU, const uint32_t *src, union mm_reg *dst, uint8_t index) {
    union vec d = { .qw = dst->qw};
    d.u16[index % 4] = (uint16_t)*src;
    dst->qw = d.qw;
}
