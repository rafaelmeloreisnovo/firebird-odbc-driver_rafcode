# Source provenance and two distinct license domains

This is a **file-scoped** license map, not a claim that the entire fork has
one interchangeable license.

| Scope | Origin | License treatment |
|---|---|---|
| Existing Firebird ODBC source files (e.g. `Main.cpp`, `Main.h`, `IscDbc/LoadFbClientDll.cpp`) | Firebird/IBPhoenix contributors | Preserve existing Initial Developer's Public License (IDPL) 1.0 notices and attribution, including contributions made to those files. |
| New independent `rafcodephi/freestanding/*` source and test files | RAFCODEPHI / Rafael Melo Reis, 2026 | MIT, as marked in those new files and `LICENSE-MIT.txt`. |
| Operating system, unixODBC, Firebird client library, build utilities and downloaded Firebird headers | Their respective publishers | Not relicensed or reproduced by this change; check each component's actual terms when packaging/distributing. |

Firebird's project licensing information:
https://www.firebirdsql.org/en/initial-developer-s-public-license-version-1-0/
and https://www.firebirdsql.org/en/odbc-driver/

A modification to an inherited IDPL source file is **not** automatically
independently MIT-licensed just because a contributor owns their additions.
Do not remove upstream notices or represent the whole driver as MIT.

The new freestanding source is *isolated*: the existing CMake production
targets, ODBC entry points, Firebird client dynamic loading and distribution
requirements remain intact. License compatibility of any future combined
binary/distribution must receive explicit review before promotion.

SOURCE != ARTIFACT != EXECUTION != EVIDENCE != CLAIM. ABI/performance gains,
end-to-end database runtime, and ARM physical-device behavior remain
TOKEN_VAZIO until exact-build receipts exist.
