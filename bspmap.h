/**
 *  @file bspmap.h
 *  @version 0.0.0
 *  @date Tue Dec  3 21:53:43 CST 2019
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#ifndef _BSPMAP_H_
#define _BSPMAP_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "bspmap"

struct bspmap;

/**
 *  @brief Create and return a new bspmap object.
 *  @details FIXME longer description here ...
 */

struct bspmap *bspmap_new(void);

/**
 *  @brief Clean up and free a bspmap structure.
 *  @details FIXME longer description here ...
 */

void        bspmap_free(struct bspmap *p);

/**
 *  @brief Initialize a bspmap object.
 *  @details FIXME longer description here ...
 *  @param p Pointer to a bspmap object
 *  @param x FIXME
 */

int         bspmap_init(struct bspmap *p, unsigned nblocks, unsigned *sblocks);


/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */

const char *bspmap_version(void);

int         bspmap_global_idx_is_valid(struct bspmap *p, unsigned gidx);
void        bspmap_global_to_local(struct bspmap *p, unsigned *bi, unsigned *bj,
                                   unsigned *bli, unsigned *blj, unsigned gi,
                                   unsigned gj);
int         bspmap_local_idx_is_valid(struct bspmap *p, unsigned bidx, unsigned blidx);
void        bspmap_local_to_global(struct bspmap *p, unsigned bi, unsigned bj,
                                   unsigned bli, unsigned blj, unsigned *gi,
                                   unsigned *gj);


#endif