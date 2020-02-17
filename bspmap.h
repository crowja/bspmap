/**
 *  @file bspmap.h
 *  @version 0.2.0-dev0
 *  @date Sun Feb 16, 2020 08:18:06 PM CST
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef BSPMAP_H
#define BSPMAP_H

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
void        bspmap_free(struct bspmap **pp);

/**
 *  @brief Initialize a bspmap object.
 *  @details FIXME longer description here ...
 *  @param pp Pointer to a bspmap object.
 *  @param x FIXME
 */
int         bspmap_init(struct bspmap *p, unsigned nblocks, unsigned *sblocks);

/**
 *  @brief Return the version of this package.
 *  @returns Version string.
 */
const char *bspmap_version(void);

/* TODO docs for each */
int         bspmap_global_idx_is_valid(struct bspmap *p, unsigned gidx);
void        bspmap_global_to_local(struct bspmap *p, unsigned *bi, unsigned *bj,
                                   unsigned *bli, unsigned *blj, unsigned gi,
                                   unsigned gj);
int         bspmap_local_idx_is_valid(struct bspmap *p, unsigned bidx, unsigned blidx);
void        bspmap_local_to_global(struct bspmap *p, unsigned bi, unsigned bj,
                                   unsigned bli, unsigned blj, unsigned *gi,
                                   unsigned *gj);

#endif
