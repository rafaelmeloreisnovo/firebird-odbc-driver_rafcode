/* SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Rafael Melo Reis
 * Host runner uses process return code; test itself does not call libc.
 */
#include "raf_span_v1.h"
#define CHECK(expr) do { if (!(expr)) ++failures; } while (0)
int main(void)
{
    int failures = 0;
    unsigned char b[8] = {'a','b','c','d','e','f',0,0};
    unsigned char out[8] = {0,0,0,0,0,0,0,0};
    raf_size index = 99;
    CHECK(raf_span_move(0, 0, 0, 0) == RAF_SPAN_OK);
    CHECK(raf_span_move(out, 2, b, 3) == RAF_SPAN_NO_SPACE);
    CHECK(out[0] == 0 && out[1] == 0);
    CHECK(raf_span_move(0, 4, b, 1) == RAF_SPAN_INVALID);
    CHECK(raf_span_move(out, 4, 0, 1) == RAF_SPAN_INVALID);
    CHECK(raf_span_move(out, 4, b, 4) == RAF_SPAN_OK);
    CHECK(out[0]=='a' && out[3]=='d' && out[4]==0);
    CHECK(raf_span_move(b+2, 4, b, 4) == RAF_SPAN_OK);
    CHECK(b[0]=='a' && b[1]=='b' && b[2]=='a' && b[3]=='b'
          && b[4]=='c' && b[5]=='d');
    CHECK(raf_span_move(b, 6, b+2, 4) == RAF_SPAN_OK);
    CHECK(b[0]=='a' && b[1]=='b' && b[2]=='c' && b[3]=='d');
    CHECK(raf_span_move(b, 8, b, 6) == RAF_SPAN_OK);
    CHECK(raf_span_find(b, 6, 'd', &index) == RAF_SPAN_OK && index == 3);
    CHECK(raf_span_find(b, 6, 'z', &index) == RAF_SPAN_NOT_FOUND && index == 3);
    CHECK(raf_span_find(0, 1, 'a', &index) == RAF_SPAN_INVALID);
    CHECK(raf_span_find(b, 6, 'a', 0) == RAF_SPAN_INVALID);
    CHECK(raf_span_find(0, 0, 0, &index) == RAF_SPAN_NOT_FOUND);
    CHECK(raf_ascii_key_equal("DBNAME",6,"dbname",6) == 1);
    CHECK(raf_ascii_key_equal("uid",3,"UID",3) == 1);
    CHECK(raf_ascii_key_equal("PWD",3,"PWN",3) == 0);
    CHECK(raf_ascii_key_equal("PWD",3,"PWD",2) == 0);
    CHECK(raf_ascii_key_equal(0,0,0,0) == 1);
    CHECK(raf_ascii_key_equal(0,1,"A",1) == 0);
    CHECK(raf_ascii_key_equal("A",1,0,1) == 0);
    CHECK(raf_ascii_key_equal("\xC3",1,"\xE3",1) == 0);
    return failures;
}
