/*	$NetBSD: keydb.h,v 1.15.2.3 2018/04/18 14:06:24 martin Exp $	*/
/*	$FreeBSD: src/sys/netipsec/keydb.h,v 1.1.4.1 2003/01/24 05:11:36 sam Exp $	*/
/*	$KAME: keydb.h,v 1.14 2000/08/02 17:58:26 sakane Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _NETIPSEC_KEYDB_H_
#define _NETIPSEC_KEYDB_H_

#ifdef _KERNEL

#include <sys/localcount.h>
#include <sys/percpu.h>

#include <netipsec/key_var.h>
#include <net/route.h>
#include <netinet/in.h>

#ifndef _SOCKADDR_UNION_DEFINED
#define _SOCKADDR_UNION_DEFINED
/*
 * The union of all possible address formats we handle.
 */
union sockaddr_union {
	struct sockaddr		sa;
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;
};
#endif /* _SOCKADDR_UNION_DEFINED */

/* Security Assocciation Index */
/* NOTE: Ensure to be same address family */
struct secasindex {
	union sockaddr_union src;	/* source address for SA */
	union sockaddr_union dst;	/* destination address for SA */
	u_int16_t proto;		/* IPPROTO_ESP or IPPROTO_AH */
	u_int8_t mode;			/* mode of protocol, see ipsec.h */
	u_int32_t reqid;		/* reqid id who owned this SA */
					/* see IPSEC_MANUAL_REQID_MAX. */
};

/* Security Association Data Base */
struct secashead {
	struct pslist_entry pslist_entry;
	struct localcount localcount;	/* reference count */

	struct secasindex saidx;

	struct sadb_ident *idents;	/* source identity */
	struct sadb_ident *identd;	/* destination identity */
					/* XXX I don't know how to use them. */
	size_t idents_len;		/* length of idents */
	size_t identd_len;		/* length of identd */

	u_int8_t state;			/* MATURE or DEAD. */
	struct pslist_head savlist[SADB_SASTATE_MAX+1];
					/* SA chain */
					/* The first of this list is newer SA */

	struct route sa_route;		/* route cache */
};

struct xformsw;
struct enc_xform;
struct auth_hash;
struct comp_algo;

/* Security Association */
struct secasvar {
	struct pslist_entry pslist_entry;
	struct pslist_entry pslist_entry_savlut;
	struct localcount localcount;	/* reference count */
	bool savlut_added;		/* Status of registration of the LUT */

	u_int8_t state;			/* Status of this Association */

	u_int8_t alg_auth;		/* Authentication Algorithm Identifier*/
	u_int8_t alg_enc;		/* Cipher Algorithm Identifier */
	u_int8_t alg_comp;		/* Compression Algorithm Identifier */
	u_int32_t spi;			/* SPI Value, network byte order */
	u_int32_t flags;		/* holder for SADB_KEY_FLAGS */

	struct sadb_key *key_auth;	/* Key for Authentication */
	size_t key_auth_len;		/* length of key_auth */
	struct sadb_key *key_enc;	/* Key for Encryption */
	size_t key_enc_len;		/* length of key_enc */
	u_int ivlen;			/* length of IV */

	struct secreplay *replay;	/* replay prevention */
	size_t replay_len;		/* length of replay */
	time_t created;			/* for lifetime */

	struct sadb_lifetime *lft_c;	/* CURRENT lifetime, it's constant. */
	struct sadb_lifetime *lft_h;	/* HARD lifetime */
	struct sadb_lifetime *lft_s;	/* SOFT lifetime */

	/* percpu counters for lft_c->sadb_lifetime_{allocations,bytes} */
	percpu_t *lft_c_counters_percpu;

	u_int32_t seq;			/* sequence number */
	pid_t pid;			/* message's pid */

	struct secashead *sah;		/* back pointer to the secashead */

	/*
	 * NB: Fields with a tdb_ prefix are part of the "glue" used
	 *     to interface to the OpenBSD crypto support.  This was done
	 *     to distinguish this code from the mainline KAME code.
	 */
	const struct xformsw *tdb_xform;	/* transform */
	const struct enc_xform *tdb_encalgxform; /* encoding algorithm */
	const struct auth_hash *tdb_authalgxform; /* authentication algorithm */
	const struct comp_algo *tdb_compalgxform; /* compression algorithm */
	u_int64_t tdb_cryptoid;		/* crypto session id */

	u_int16_t natt_type;
	u_int16_t esp_frag;
};

/* replay prevention */
struct secreplay {
	u_int32_t count;
	u_int wsize;		/* window size, i.g. 4 bytes */
	u_int32_t seq;		/* used by sender */
	u_int32_t lastseq;	/* used by receiver */
	char *bitmap;		/* used by receiver */
	int overflow;		/* overflow flag */
};

/* socket table due to send PF_KEY messages. */
struct secreg {
	LIST_ENTRY(secreg) chain;

	struct socket *so;
};

#ifndef IPSEC_NONBLOCK_ACQUIRE
/* acquiring list table. */
struct secacq {
	LIST_ENTRY(secacq) chain;

	struct secasindex saidx;

	u_int32_t seq;		/* sequence number */
	time_t created;		/* for lifetime */
	int count;		/* for lifetime */
};
#endif

/* Sensitivity Level Specification */
/* nothing */

#define SADB_KILL_INTERVAL	600	/* six seconds */

/* secpolicy */
struct secpolicy *keydb_newsecpolicy (void);
void keydb_delsecpolicy (struct secpolicy *);
/* secashead */
struct secashead *keydb_newsecashead (void);
void keydb_delsecashead (struct secashead *);
/* secasvar */
struct secasvar *keydb_newsecasvar (void);
void keydb_refsecasvar (struct secasvar *);
void keydb_freesecasvar (struct secasvar *);
/* secreplay */
struct secreplay *keydb_newsecreplay (size_t);
void keydb_delsecreplay (struct secreplay *);
/* secreg */
struct secreg *keydb_newsecreg (void);
void keydb_delsecreg (struct secreg *);

#endif /* _KERNEL */

#endif /* !_NETIPSEC_KEYDB_H_ */
