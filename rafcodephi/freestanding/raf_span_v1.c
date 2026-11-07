/* SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Rafael Melo Reis
 * Pure C11, no libc, allocator, I/O, global state, system calls, or OS headers.
 */
#include "raf_span_v1.h"
int raf_span_move(void *dst, raf_size capacity, const void *src, raf_size length)
{
    unsigned char *d;
    const unsigned char *s;
    raf_size i;
    if (length > capacity)
        return RAF_SPAN_NO_SPACE;
    if (length == 0)
        return RAF_SPAN_OK;
    if (!dst || !src)
        return RAF_SPAN_INVALID;
    if (dst == src)
        return RAF_SPAN_OK;
    d = (unsigned char *)dst;
    s = (const unsigned char *)src;
    /* Integer address comparison avoids undefined relational comparison of
     * pointers to unrelated C objects. Assumes flat GCC/Clang target ABI. */
    if ((raf_uptr)d > (raf_uptr)s &&
        ((raf_uptr)d - (raf_uptr)s) < length) {
        i = length;
        while (i != 0) {
            --i;
            d[i] = s[i];
        }
    } else {
        for (i = 0; i < length; ++i)
            d[i] = s[i];
    }
    return RAF_SPAN_OK;
}
int raf_span_find(const void *data, raf_size length, unsigned char needle,
                  raf_size *index)
{
    const unsigned char *p = (const unsigned char *)data;
    raf_size i;
    if (!index || (length != 0 && !p))
        return RAF_SPAN_INVALID;
    for (i = 0; i < length; ++i) {
        if (p[i] == needle) {
            *index = i;
            return RAF_SPAN_OK;
        }
    }
    return RAF_SPAN_NOT_FOUND;
}
static unsigned char raf_ascii_fold(unsigned char ch)
{
    if (ch >= (unsigned char)'A' && ch <= (unsigned char)'Z')
        return (unsigned char)(ch + (unsigned char)('a' - 'A'));
    return ch;
}
int raf_ascii_key_equal(const void *left, raf_size left_len,
                        const void *right, raf_size right_len)
{
    const unsigned char *a = (const unsigned char *)left;
    const unsigned char *b = (const unsigned char *)right;
    raf_size i;
    if (left_len != right_len)
        return 0;
    if (left_len == 0)
        return 1;
    if (!a || !b)
        return 0;
    for (i = 0; i < left_len; ++i) {
        if (raf_ascii_fold(a[i]) != raf_ascii_fold(b[i]))
            return 0;
    }
    return 1;
}
