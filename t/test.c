#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "bspmap.h"
#include "t/tinytest.h"
#include "t/tinyhelp.h"

static void
test_constr(void)
{
   struct bspmap *z;

   fprintf_test_info(stdout, "test_constr", "bspmap_new, bspmap_free");
   z = bspmap_new();
   ASSERT("Constructor test", z);
   bspmap_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_global_to_local(void)
{
   struct bspmap *z = bspmap_new();
   unsigned    sblocks[] = { 3, 4, 5 };
   unsigned    nblocks = 3;
   unsigned    bi, bj;
   unsigned    bli, blj;
   unsigned    gi, gj;

   fprintf_test_info(stdout, "test_global_to_local", "bspmap_global_to_local");
   bspmap_init(z, nblocks, sblocks);

   gi = 0;
   gj = 0;
   bspmap_global_to_local(z, &bi, &bj, &bli, &blj, gi, gj);
   ASSERT_EQUALS(bi, 0);
   ASSERT_EQUALS(bj, 0);
   ASSERT_EQUALS(bli, 0);
   ASSERT_EQUALS(blj, 0);

   gi = 7;
   gj = 8;
   bspmap_global_to_local(z, &bi, &bj, &bli, &blj, gi, gj);
   ASSERT_EQUALS(bi, 2);
   ASSERT_EQUALS(bj, 2);
   ASSERT_EQUALS(bli, 0);
   ASSERT_EQUALS(blj, 1);

   gi = 11;
   gj = 11;
   bspmap_global_to_local(z, &bi, &bj, &bli, &blj, gi, gj);
   ASSERT_EQUALS(bi, 2);
   ASSERT_EQUALS(bj, 2);
   ASSERT_EQUALS(bli, 4);
   ASSERT_EQUALS(blj, 4);

   bspmap_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_local_to_global(void)
{
   struct bspmap *z = bspmap_new();
   unsigned    sblocks[] = { 3, 4, 5 };
   unsigned    nblocks = 3;
   unsigned    bi, bj;
   unsigned    bli, blj;
   unsigned    gi, gj;

   fprintf_test_info(stdout, "test_local_to_global", "bspmap_local_to_global");

   bspmap_init(z, nblocks, sblocks);

   bi = 0;
   bj = 0;
   bli = 0;
   blj = 0;
   bspmap_local_to_global(z, bi, bj, bli, blj, &gi, &gj);
   ASSERT_EQUALS(gi, 0);
   ASSERT_EQUALS(gj, 0);

   bi = 2;
   bj = 2;
   bli = 4;
   blj = 4;
   bspmap_local_to_global(z, bi, bj, bli, blj, &gi, &gj);
   ASSERT_EQUALS(gi, 11);
   ASSERT_EQUALS(gj, 11);

   bi = 2;
   bj = 2;
   bli = 0;
   blj = 1;
   bspmap_local_to_global(z, bi, bj, bli, blj, &gi, &gj);
   ASSERT_EQUALS(gi, 7);
   ASSERT_EQUALS(gj, 8);

   bspmap_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_local_and_global_stress(void)
{
   struct bspmap *z = bspmap_new();
   unsigned    sblocks[] = { 3, 40, 5, 6, 7, 1, 1, 10 };
   unsigned    nblocks = 8;                 /* needs to reflect above */
   unsigned    bi, bj;
   unsigned    bli, blj;
   unsigned    gi, gj;
   unsigned    tgi, tgj;
   unsigned    k, n;

   fprintf_test_info(stdout, "test_local_and_global_stress",
                    "bspmap_local_to_global, bspmap_global_to_local");

   for (k = 0, n = 0; k < nblocks; k++)
      n += sblocks[k];

   bspmap_init(z, nblocks, sblocks);

   for (gi = 0; gi < n; gi++) {
      for (gj = 0; gj < n; gj++) {
         bspmap_global_to_local(z, &bi, &bj, &bli, &blj, gi, gj);
         bspmap_local_to_global(z, bi, bj, bli, blj, &tgi, &tgj);
         ASSERT_EQUALS(gi, tgi);
         ASSERT_EQUALS(gj, tgj);
      }
   }
   bspmap_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_check_local_idx(void)
{
   struct bspmap *z = bspmap_new();
   unsigned    sblocks[] = { 3, 40, 5, 6, 7, 1, 1, 10 };
   unsigned    nblocks = 8;                 /* needs to reflect above */
   unsigned    k, n;

   fprintf_test_info(stdout, "test_check_local_idx", "bspmap_local_idx_is_valid");

   for (k = 0, n = 0; k < nblocks; k++)
      n += sblocks[k];

   bspmap_init(z, nblocks, sblocks);

   ASSERT_EQUALS(1, bspmap_local_idx_is_valid(z, 0, 0));
   ASSERT_EQUALS(1, bspmap_local_idx_is_valid(z, 1, 39));
   ASSERT_EQUALS(0, bspmap_local_idx_is_valid(z, 1, 40));
   ASSERT_EQUALS(1, bspmap_local_idx_is_valid(z, 2, 4));
   ASSERT_EQUALS(0, bspmap_local_idx_is_valid(z, 2, 5));
   ASSERT_EQUALS(1, bspmap_local_idx_is_valid(z, 7, 9));
   ASSERT_EQUALS(0, bspmap_local_idx_is_valid(z, 7, 10));
   ASSERT_EQUALS(0, bspmap_local_idx_is_valid(z, 8, 0));

   bspmap_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_check_global_idx(void)
{
   struct bspmap *z = bspmap_new();
   unsigned    sblocks[] = { 3, 40, 5, 6, 7, 1, 1, 10 };
   unsigned    nblocks = 8;                 /* needs to reflect above */
   unsigned    k, n;

   fprintf_test_info(stdout, "test_check_global_idx", "bspmap_global_idx_is_valid");

   for (k = 0, n = 0; k < nblocks; k++)
      n += sblocks[k];

   bspmap_init(z, nblocks, sblocks);

   /* All pass */
   for (k = 0; k < n; k++)
      ASSERT_EQUALS(1, bspmap_global_idx_is_valid(z, k));

   /* All fail */
   for (k = n; k < 2 * n; k++)
      ASSERT_EQUALS(0, bspmap_global_idx_is_valid(z, k));

   bspmap_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#if 0                                            /* 10 yy */
static void
test_stub(void)
{
   struct bspmap *z;

   fprintf_test_info(stdout, "test_stub", NULL);
   z = bspmap_new();
   bspmap_free(&z);
   ASSERT_EQUALS(NULL, z);
}
#endif

int
main(void)
{
   printf("%s\n", bspmap_version());

   RUN(test_constr);
   RUN(test_global_to_local);
   RUN(test_local_to_global);
   RUN(test_local_and_global_stress);
   RUN(test_check_local_idx);
   RUN(test_check_global_idx);

   return TEST_REPORT();
}
