## Succinct data structures

Suppose we have an operation
$\star\colon\Omega\times\Omega\mapsto\Omega$. We're supposed to pre-process a
given array a[0..n) so that we support the following operations.

 - `accumulate(i, j)`: return a[i] * a[i+1] * ... * a[j]
 - `update(i, v)`: set a[i] <- v

If * is a group, single [Fenwick array](./fenwick.cpp) suffices.
If * is a semi-group, then we need something with more bookkeeping.
Segment tree achieves $2n$ storage (up from $n$ storage of Fenwick). See
[segment tree](./segt.cpp).

## Examples

See [lis-k](./lis-k.cpp) for an example  which can be implemented via a segment
tree or double fenwick tree.
