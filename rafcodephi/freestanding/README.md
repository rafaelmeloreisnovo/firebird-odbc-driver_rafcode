# RAFCODEPHI isolated freestanding core (V1)

Original source in this directory is independently authored and MIT licensed
(see `LICENSE-MIT.txt`). The inherited Firebird ODBC sources remain under their
own pre-existing file-level licenses, chiefly IDPL 1.0. Nothing here relicenses
Firebird, unixODBC, or Firebird client binaries.

## Boundary / verified design intent

`raf_span_v1.[ch]` is C11, no standard-library headers, heap, shared mutable
state, I/O or OS syscalls. `raf_size` and `raf_uptr` deliberately use the
GCC/Clang target's built-in types. Supported flat-address targets for the
original kernel are x86_64, ARMv7 and AArch64. A host program can run the
tests, but the kernel itself does not invoke the host runtime.

Contracts: caller supplies **valid readable/writable spans**; no function
can validate whether a non-null pointer points to live storage. The move
function checks output capacity before modifying any bytes, accepts zero
length with null pointers, and supports overlapping spans. It cannot prevent
an incorrect input buffer length or use-after-free supplied by its caller.
The key comparison is ASCII-only, not Unicode collation.

Compile example (no external headers, optional shell runner):

```sh
cc -std=c11 -O2 -ffreestanding -fno-builtin -fno-stack-protector \
  -nostdinc -Wall -Wextra -Werror -pedantic \
  -c rafcodephi/freestanding/raf_span_v1.c -o raf_span_v1.o
nm -u raf_span_v1.o  # must show no undefined symbols
cc -std=c11 -O2 -Wall -Wextra -Werror -pedantic \
  rafcodephi/freestanding/raf_span_v1.c \
  rafcodephi/freestanding/test_raf_span_v1.c -o raf_span_test
./raf_span_test
```

The module is **not connected to the production ODBC dispatch path** yet:
this avoids a premature ABI/behavior change. Follow-up integration needs
independent ODBC tests, Firebird 3+/4/5 connections, thread/cancel scenarios,
ASan/UBSan, and hardware measurements before performance claims.

No inline ASM or hex literals are used as performance decorations. Add
optional ISA-specific assembly only after a disassembly/benchmark comparison
against compiler output, preserving C fallback, ABI, tests and rollback.

Licensing and legal notices: `../../LICENSES/PROVENANCE.md`.
