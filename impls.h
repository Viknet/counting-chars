#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <arm_neon.h>

unsigned long fps_count_naive(unsigned char *str, unsigned long len, unsigned char w) {
    unsigned long c;
    for (c = 0; len-- != 0; ++str)
        if (*str == w)
            ++c;
    return c;
}

unsigned long fps_count_neon(unsigned char *str, unsigned long len, unsigned char w) {
    const uint8x16_t pat = vdupq_n_u8(w);

    unsigned long res = 0;

    size_t i = 0;

    for (; i < len && (intptr_t)(str + i) % 64; ++i) {
        res += str[i] == w;
    }

    for (unsigned long end = len - 128; i < end; i += 128) {
        uint8x16_t p0 = vld1q_u8((const uint8x16_t*)(str + i + 16 * 0));
        uint8x16_t p1 = vld1q_u8((const uint8x16_t*)(str + i + 16 * 1));
        uint8x16_t p2 = vld1q_u8((const uint8x16_t*)(str + i + 16 * 2));
        uint8x16_t p3 = vld1q_u8((const uint8x16_t*)(str + i + 16 * 3));
        uint8x16_t p4 = vld1q_u8((const uint8x16_t*)(str + i + 16 * 4));
        uint8x16_t p5 = vld1q_u8((const uint8x16_t*)(str + i + 16 * 5));
        uint8x16_t p6 = vld1q_u8((const uint8x16_t*)(str + i + 16 * 6));
        uint8x16_t p7 = vld1q_u8((const uint8x16_t*)(str + i + 16 * 7));
        uint8x16_t r0 = vceqq_u8(p0, pat);
        uint8x16_t r1 = vceqq_u8(p1, pat);
        uint8x16_t r2 = vceqq_u8(p2, pat);
        uint8x16_t r3 = vceqq_u8(p3, pat);
        uint8x16_t r4 = vceqq_u8(p4, pat);
        uint8x16_t r5 = vceqq_u8(p5, pat);
        uint8x16_t r6 = vceqq_u8(p6, pat);
        uint8x16_t r7 = vceqq_u8(p7, pat);
        res += (__builtin_popcountll(vgetq_lane_u64(r0, 0)) + __builtin_popcountll(vgetq_lane_u64(r0, 1))) >> 3;
        res += (__builtin_popcountll(vgetq_lane_u64(r1, 0)) + __builtin_popcountll(vgetq_lane_u64(r1, 1))) >> 3;
        res += (__builtin_popcountll(vgetq_lane_u64(r2, 0)) + __builtin_popcountll(vgetq_lane_u64(r2, 1))) >> 3;
        res += (__builtin_popcountll(vgetq_lane_u64(r3, 0)) + __builtin_popcountll(vgetq_lane_u64(r3, 1))) >> 3;
        res += (__builtin_popcountll(vgetq_lane_u64(r4, 0)) + __builtin_popcountll(vgetq_lane_u64(r4, 1))) >> 3;
        res += (__builtin_popcountll(vgetq_lane_u64(r5, 0)) + __builtin_popcountll(vgetq_lane_u64(r5, 1))) >> 3;
        res += (__builtin_popcountll(vgetq_lane_u64(r6, 0)) + __builtin_popcountll(vgetq_lane_u64(r6, 1))) >> 3;
        res += (__builtin_popcountll(vgetq_lane_u64(r7, 0)) + __builtin_popcountll(vgetq_lane_u64(r7, 1))) >> 3;
    }

    for (; i < len; ++i) {
        res += str[i] == w;
    }

    return res;
}
