## Ladder

Often we have data points $(x,y)$ with domination order:
$(x_1,y_1) \le (x_2, y_2)$ if both $x_1\le x_2$ and $y_1 \le y_2$.
In such cases, if we are to maintain a list of non-dominated points
(say, $m$ of them), we end up with the ladder structure: 
$x_1 \le x_2 \le \cdots \le x_m$ and
$y_1 \ge y_2 \ge \cdots \ge y_m$.

Pictorially, this is a ladder that goes down right. Depending on what operations
we need to support, a ladder can be maintained via an array, stack, heap or
segment tree (in increasing flexibility but complexity).

The simplest case is append to right and increase-y operations. This can be
handled with a single array. See [LIS](../bsearch/lis.cpp) problem (in this
viewpoint, y coordinate of the LIS problem is inverted).
