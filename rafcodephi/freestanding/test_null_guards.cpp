/* SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Rafael Melo Reis
 * Host-only compatibility smoke test of inherited IDPL Main.h macros.
 */
#define DRIVER_LOCKED_LEVEL_ENV 1
#define DRIVER_LOCKED_LEVEL_CONNECT 2
#ifndef DRIVER_LOCKED_LEVEL
#define DRIVER_LOCKED_LEVEL DRIVER_LOCKED_LEVEL_CONNECT
#endif
#define SQL_INVALID_HANDLE (-2)
#define SQL_HANDLE_DBC 2
#define SQL_HANDLE_STMT 3
#define SQL_HANDLE_DESC 4
#ifndef NULL
#define NULL 0
#endif
struct OdbcEnv {};
struct OdbcConnection {};
struct OdbcStatement { OdbcConnection *connection; };
struct OdbcDesc { OdbcConnection *connection; };
struct SafeDllThread { SafeDllThread() {} };
struct SafeEnvThread { explicit SafeEnvThread(OdbcEnv *) {} };
struct SafeConnectThread { explicit SafeConnectThread(OdbcConnection *) {} };
#include "../../Main.h"
static int env_test(OdbcEnv *v) { GUARD_ENV(v); return 0; }
static int dbc_test(OdbcConnection *v) { GUARD_HDBC(v); return 0; }
static int stmt_test(OdbcStatement *v) { GUARD_HSTMT(v); return 0; }
static int desc_test(OdbcDesc *v) { GUARD_HDESC(v); return 0; }
static int type_test(void *v, int t) { GUARD_HTYPE(v,t); return 0; }
int main()
{
    OdbcEnv e;
    OdbcConnection c;
    OdbcStatement s = {&c};
    OdbcDesc d = {&c};
    if (env_test(0) != SQL_INVALID_HANDLE || dbc_test(0) != SQL_INVALID_HANDLE
        || stmt_test(0) != SQL_INVALID_HANDLE
        || desc_test(0) != SQL_INVALID_HANDLE
        || type_test(0, SQL_HANDLE_DBC) != SQL_INVALID_HANDLE)
        return 1;
    if (env_test(&e) || dbc_test(&c) || stmt_test(&s) || desc_test(&d)
        || type_test(&c,SQL_HANDLE_DBC) || type_test(&s,SQL_HANDLE_STMT)
        || type_test(&d,SQL_HANDLE_DESC))
        return 2;
    return 0;
}
