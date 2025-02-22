/****************************************************************************
 * bfs                                                                      *
 * Copyright (C) 2019-2020 Tavian Barnes <tavianator@tavianator.com>        *
 *                                                                          *
 * Permission to use, copy, modify, and/or distribute this software for any *
 * purpose with or without fee is hereby granted.                           *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES *
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF         *
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR  *
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES   *
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN    *
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF  *
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.           *
 ****************************************************************************/

/**
 * A facade over (file)system features that are (un)implemented differently
 * between platforms.
 */

#ifndef BFS_FSADE_H
#define BFS_FSADE_H

#include "config.h"
#include <stdbool.h>

#define BFS_CAN_CHECK_ACL BFS_USE_SYS_ACL_H

#if !defined(BFS_CAN_CHECK_CAPABILITIES) && BFS_USE_SYS_CAPABILITY_H && !__FreeBSD__
#	include <sys/capability.h>
#	ifdef CAP_CHOWN
#		define BFS_CAN_CHECK_CAPABILITIES true
#	endif
#endif

#define BFS_CAN_CHECK_XATTRS (BFS_USE_SYS_EXTATTR_H || BFS_USE_SYS_XATTR_H)

struct BFTW;

/**
 * Check if a file has a non-trivial Access Control List.
 *
 * @param ftwbuf
 *         The file to check.
 * @return
 *         1 if it does, 0 if it doesn't, or -1 if an error occurred.
 */
int bfs_check_acl(const struct BFTW *ftwbuf);

/**
 * Check if a file has a non-trivial capability set.
 *
 * @param ftwbuf
 *         The file to check.
 * @return
 *         1 if it does, 0 if it doesn't, or -1 if an error occurred.
 */
int bfs_check_capabilities(const struct BFTW *ftwbuf);

/**
 * Check if a file has any extended attributes set.
 *
 * @param ftwbuf
 *         The file to check.
 * @return
 *         1 if it does, 0 if it doesn't, or -1 if an error occurred.
 */
int bfs_check_xattrs(const struct BFTW *ftwbuf);

/**
 * Check if a file has an extended attribute with the given name.
 *
 * @param ftwbuf
 *         The file to check.
 * @param name
 *         The name of the xattr to check.
 * @return
 *         1 if it does, 0 if it doesn't, or -1 if an error occurred.
 */
int bfs_check_xattr_named(const struct BFTW *ftwbuf, const char *name);

#endif // BFS_FSADE_H
