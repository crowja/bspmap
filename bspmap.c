/**
 *  @file bspmap.c
 *  @version 0.2.0-dev0
 *  @date Sun Feb 16, 2020 08:18:06 PM CST
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <string.h>                              /* FIXME */
#include "bspmap.h"

#ifdef  IS_NULL
#undef  IS_NULL
#endif
#define IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  FREE
#undef  FREE
#endif
#define FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

struct bspmap {
   void       *x;
   unsigned    nblocks;
   unsigned   *cblocks;
};

struct bspmap *
bspmap_new(void)
{
   struct bspmap *tp;

   tp = (struct bspmap *) malloc(sizeof(struct bspmap));
   if (IS_NULL(tp))
      return NULL;

   tp->nblocks = 0;
   tp->cblocks = NULL;

   return tp;
}

void
bspmap_free(struct bspmap **pp)
{

   FREE((*pp)->cblocks);
   FREE(*pp);
   *pp = NULL;
}

int
bspmap_init(struct bspmap *p, unsigned nblocks, unsigned *sblocks)
{
   unsigned    k;

   p->nblocks = nblocks;
   p->cblocks = realloc(p->cblocks, nblocks * sizeof(unsigned));

   (p->cblocks)[0] = sblocks[0];

   for (k = 1; k < nblocks; k++)
      (p->cblocks)[k] = sblocks[k] + (p->cblocks)[k - 1];

   return 0;
}

const char *
bspmap_version(void)
{
   return "0.2.0-dev0";
}

int
bspmap_global_idx_is_valid(struct bspmap *p, unsigned gidx)
{
   return gidx < (p->cblocks)[p->nblocks - 1];
}

void
bspmap_global_to_local(struct bspmap *p, unsigned *bi, unsigned *bj, unsigned *bli,
                       unsigned *blj, unsigned gi, unsigned gj)
{
   unsigned    k;

   /* Assumes gi, gj are valid */

   if (gi < (p->cblocks)[0]) {
      *bi = 0;
      *bli = gi;
   }
   else {
      for (k = 1; k < p->nblocks; k++)
         if (gi < (p->cblocks)[k]) {
            *bi = k;
            *bli = gi - (p->cblocks)[k - 1];
            break;
         }
   }

   if (gj < (p->cblocks)[0]) {
      *bj = 0;
      *blj = gj;
   }
   else {
      for (k = 1; k < p->nblocks; k++)
         if (gj < (p->cblocks)[k]) {
            *bj = k;
            *blj = gj - (p->cblocks)[k - 1];
            break;
         }
   }
}

int
bspmap_local_idx_is_valid(struct bspmap *p, unsigned bidx, unsigned blidx)
{
   /* Check if bidx and blidx are valid block and block-local indices */
   if (bidx < p->nblocks) {                      /* check block index */
      if (bidx == 0)
         return blidx < (p->cblocks)[0];
      else
         return blidx < (p->cblocks)[bidx] - (p->cblocks)[bidx - 1];
   }

   return 0;                                     /* not a valid local index */
}

void
bspmap_local_to_global(struct bspmap *p, unsigned bi, unsigned bj, unsigned bli,
                       unsigned blj, unsigned *gi, unsigned *gj)
{
   /* Assumes bi, bj are valid and and bli, blj are valid for each block */

   if (bi > 0)
      *gi = (p->cblocks)[bi - 1] + bli;
   else
      *gi = bli;

   if (bj > 0)
      *gj = (p->cblocks)[bj - 1] + blj;
   else
      *gj = blj;
}

#undef  IS_NULL
#undef  FREE
