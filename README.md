# bspmap 0.1.1-dev0

Coordinate/index mappers for block sparse matrices.

A block sparse matrix here is one which is:

*   Square.
*   Sparse.
*   Can be viewed as based on blocks.

Such a matrix looks like:

    B[0, 0]              . . .    B[0, nblocks - 1]
     .        .                    .
     .               .             .
     .                      .      .

    B[nblocks - 1, 0]    . . .    B[nblocks - 1, nblocks - 1]

where the diagonal blocks B[k, k] are square.

This is a natural situation. If a physical domain is partitioned into nblocks
local domains, a block sparse matrix might represent the interactions between
each domain.
