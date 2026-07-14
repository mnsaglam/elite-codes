Suppose we have an operation
$\star\colon\Omega\times\Omega\mapsto\Omega$. We're suppose to pre-process a
given array a[0..n) so that we support the following operations.

 - Range accumulate: a[i] * a[i+1] * ... * a[j]
 - Update: a[i] <- v

If * is a group, single [Fenwick array](./fenwick.cpp) suffices.
If * is a semi group, then we need something with more bookkeeping.
Segment tree achieves 2n storage (up from n storage of Fenwick). See
[segment tree](./segt.cpp).
