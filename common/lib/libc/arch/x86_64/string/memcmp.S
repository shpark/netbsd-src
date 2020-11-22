/*
 * Written by J.T. Conklin <jtc@NetBSD.org>.
 * Public domain.
 * Adapted for NetBSD/x86_64 by Frank van der Linden <fvdl@wasabisystems.com>
 */

#include <machine/asm.h>

#if defined(LIBC_SCCS)
	RCSID("$NetBSD: memcmp.S,v 1.3 2014/03/22 19:16:34 jakllsch Exp $")
#endif

ENTRY(memcmp)
    test   %rdx,%rdx
    je     L5
    xor    %ecx,%ecx
    nopl   0x0(%rax,%rax,1)
L4: movzbl (%rdi,%rcx,1),%eax
    movzbl (%rsi,%rcx,1),%r8d
    cmp    %r8b,%al
    jne    L6
    add    $0x1,%rcx
    cmp    %rcx,%rdx
    jne    L4
L5: xor    %eax,%eax
    retq
L6: sub    %r8d,%eax
    retq
    xchg   %ax,%ax
END(memcmp)
