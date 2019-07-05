/* EINA - EFL data type library
 * Copyright (C) 2007-2008 Jorge Luis Zapata Muga
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EINA_MEMPOOL_H_
#define EINA_MEMPOOL_H_

#include "eina_types.h"
#include "eina_error.h"
#include "eina_module.h"


/**
 * @addtogroup Eina_Memory_Pool_Group Memory Pool
 *
 * @brief These functions provide memory pool management.
 *
 * Several mempool are available:
 *
 * @li @c buddy: It uses the
 * <a href="http://en.wikipedia.org/wiki/Buddy_memory_allocation">"buddy
 * allocator" algorithm</a> but the Eina implementation differs in the
 * sense that the chunk information is not stored on the chunk itself,
 * but on another memory area. This is useful for cases where the
 * memory to manage might be slower to access, or limited (like video
 * memory).
 * @li @c chained_pool: It is the default one. It allocates a big
 * chunk of memory with malloc() and split the result in chunks of the
 * requested size that are pushed inside a stack. When requested, it
 * takes this pointer from the stack to give them to whoever wants
 * them.
 * @li @c ememoa_fixed and @c ememoa_unknown: experimental allocators
 * which could be useful when a fixed amount of memory is needed.
 * @li @c fixed_bitmap: It allocates with malloc) 32* the requested
 * size and push the pool pointer in an rbtree. To find empty space in
 * a pool, it will just search for the first bit set in an int (32
 * bits). Then, when a pointer is freed, it will do a search inside
 * the rbtree.
 * @li @c pass_through: it just call malloc() and free(). It may be
 * faster on some computers than using our own allocators (like having
 * a huge L2 cache, over 4MB).
 * @li @c one_big: It call just one time malloc for the requested number
 * of items. Useful when you know in advance how many object of some
 * type will live during the life of the mempool.
 */

/**
 * @addtogroup Eina_Tools_Group Tools
 *
 * @{
 */

/**
 * @defgroup Eina_Memory_Pool_Group Memory Pool
 *
 * @{
 */

/**
 * @typedef Eina_Mempool
 * Mempool type.
 */
typedef struct _Eina_Mempool Eina_Mempool;

/**
 * @typedef Eina_Mempool_Backend
 * Mempool backend type.
 */
typedef struct _Eina_Mempool_Backend Eina_Mempool_Backend;


/**
 * @typedef Eina_Mempool_Repack_Cb
 * Type for a callback who need to unreference an old object from a mempool
 * and reference the new one instead. Memcpy is taken care by the mempool.
 */
typedef void (*Eina_Mempool_Repack_Cb)(void *dst, void *src, void *data);

EAPI extern Eina_Error EINA_ERROR_NOT_MEMPOOL_MODULE;

EAPI Eina_Mempool  *eina_mempool_add(const char *module, const char *context, const char *options, ...) EINA_MALLOC EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1);
EAPI void           eina_mempool_del(Eina_Mempool *mp) EINA_ARG_NONNULL(1);

static inline void *eina_mempool_realloc(Eina_Mempool *mp, void *element, unsigned int size) EINA_ARG_NONNULL(1) EINA_WARN_UNUSED_RESULT;
static inline void *eina_mempool_malloc(Eina_Mempool *mp, unsigned int size) EINA_MALLOC EINA_ARG_NONNULL(1) EINA_WARN_UNUSED_RESULT;
static inline void  eina_mempool_free(Eina_Mempool *mp, void *element) EINA_ARG_NONNULL(1);

EAPI void	    eina_mempool_repack(Eina_Mempool *mp,
				        Eina_Mempool_Repack_Cb cb,
					void *data) EINA_ARG_NONNULL(1, 2);
EAPI void           eina_mempool_gc(Eina_Mempool *mp) EINA_ARG_NONNULL(1);
EAPI void           eina_mempool_statistics(Eina_Mempool *mp) EINA_ARG_NONNULL(1);

EAPI Eina_Bool      eina_mempool_register(Eina_Mempool_Backend *be) EINA_ARG_NONNULL(1);
EAPI void           eina_mempool_unregister(Eina_Mempool_Backend *be) EINA_ARG_NONNULL(1);

EAPI unsigned int   eina_mempool_alignof(unsigned int size);

#include "eina_inline_mempool.x"

/**
 * @}
 */

/**
 * @}
 */

#endif /* EINA_MEMPOOL_H_ */
