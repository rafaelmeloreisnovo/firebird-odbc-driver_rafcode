/* SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Rafael Melo Reis
 * Independent RAFCODEPHI code; not derived from Firebird ODBC.
 */
#ifndef RAF_SPAN_V1_H
#define RAF_SPAN_V1_H
#if !defined(__SIZE_TYPE__) || !defined(__UINTPTR_TYPE__)
#error "raf_span_v1 requires GCC/Clang size and uintptr built-in types"
#endif
typedef __SIZE_TYPE__ raf_size;
typedef __UINTPTR_TYPE__ raf_uptr;
enum {
    RAF_SPAN_OK = 0,
    RAF_SPAN_INVALID = -1,
    RAF_SPAN_NO_SPACE = -2,
    RAF_SPAN_NOT_FOUND = -3
};
#ifdef __cplusplus
extern "C" {
#endif
/* Precondition: src references at least length readable bytes; dst has capacity
 * writable bytes. Overlap is supported. No partial writes on argument failure. */
int raf_span_move(void *dst, raf_size capacity, const void *src, raf_size length);
/* *index is modified only when the byte is found. */
int raf_span_find(const void *data, raf_size length, unsigned char needle,
                  raf_size *index);
/* ASCII-only, length-bounded comparison of connection-key byte sequences. */
int raf_ascii_key_equal(const void *left, raf_size left_len,
                        const void *right, raf_size right_len);
#ifdef __cplusplus
}
#endif
#endif
