*This project has been created as part of the 42 curriculum by kwlodars and pkruszyn*

# Push_swap
 
## Description
 Sorts integers with two stacks and 11 allowed moves. Prints the moves, not the result.
 
The interesting part isn't sorting. It's that the same 500 numbers take 33044 moves or
5539 depending on which algorithm you pick. Four strategies live in one binary. It picks
one at runtime from a measured *disorder* value, or you force one with a flag.
 
Moves: `sa` `sb` `ss` `pa` `pb` `ra` `rb` `rr` `rra` `rrb` `rrr`.
 
## Build
 
```bash
make        # ./push_swap
make clean  # objects
make fclean # objects + binary
make re
```
 
`cc -Wall -Wextra -Werror`. libft builds first. No relink.
 
## Run
 
```bash
./push_swap [strategy] [--bench] <integers>
```
 
| Flag | Effect |
|---|---|
| `--simple` | force O(n²) |
| `--medium` | force O(n√n) |
| `--complex` | force O(n log n) |
| `--adaptive` | pick by disorder — **default** |
| `--bench` | metrics on stderr |
 
Strategy flags are exclusive — two of them is an error. `--bench` combines with any.
Flags go before the numbers.
 
Numbers come as separate args or as one string: `./push_swap 3 1 2` and
`./push_swap "3 1 2"` both work, mixed too. Shells disagree about splitting `$VAR`, so
we handle both.
 
stdout is moves and nothing else. stderr is `Error` and `[bench]` lines. No args or
already-sorted input prints nothing, exits 0.
 
Linux.
 
## Examples
 
```bash
$> ./push_swap 2 1 3 6 5 8
ra
pb
...
 
$> ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l
13
 
$> ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
OK
 
$> shuf -i 0-9999 -n 500 > args.txt ; ./push_swap $(cat args.txt) | wc -l
5539
 
$> shuf -i 0-9999 -n 500 > args.txt ; ./push_swap --bench $(cat args.txt) 2> bench.txt | ./checker_linux $(cat args.txt)
OK
$> cat bench.txt
[bench] disorder:  49.93%
[bench] strategy:  Adaptive / O(n√n)
[bench] total_ops:  5539
[bench] sa: 0  sb: 0  ss: 0  pa: 500  pb: 500
[bench] ra: 2891  rb: 812  rr: 0  rra: 0  rrb: 836  rrr: 0
 
$> ./push_swap --adaptive 0 one 2 3
Error
$> ./push_swap --simple 3 2 3
Error
```
 
## Layout
 
```
push_swap/
├── Makefile
├── includes/
│   └── push_swap.h       types, enums, prototypes
├── libft/
└── srcs/
    ├── main.c            init, dispatch
    ├── parse.c           tokenise args, build stack a
    ├── flags.c           flags, mutual exclusion
    ├── validate.c        syntax, int range, duplicates, error exit
    ├── stack_v1.c           node/list primitives
    ├── stack_v2.c           node/list primitives
    ├── ops_swap.c        sa, sb, ss
    ├── ops_push.c        pa, pb
    ├── ops_rotate.c      ra, rb, rr
    ├── ops_rrotate.c     rra, rrb, rrr
    ├── disorder.c        compute_disorder
    ├── sort_small.c      n ≤ 3, hard-coded
    ├── sort_simple.c     selection      O(n²)
    ├── sort_medium_v1.c     chunks         O(n√n)
    ├── sort_medium_v2.c     chunks         O(n√n)
    ├── sort_complex.c    binary radix   O(n log n)
    ├── sort_adaptive.c   router
    ├── bench.c           --bench
    └── utils.c           indexing_stack, is_sorted, min/max position
```
 
Calls only go downwards:
 
```
              main.c                    dispatch
                 │
     ┌───────────┼────────────┐
     ▼           ▼            ▼
  parse.c    sort_*.c      bench.c      input / strategies / reporting
  flags.c        │            │
  validate.c     │            │
     │           │            │
     └───────────┼────────────┘
                 ▼
              ops_*.c                   only writers to stdout
                 │
                 ▼
              stack.c                   pointer wrangling
```
 
Strategies never touch node pointers and never print. They decide *which* move to emit.
One wrapper per move does the rewiring, the print and the counter bump, so emitted lines
and benchmark totals can't drift.
 
## Flow
 
```
argv
 │
 ▼  init_ps                  zeroed, strategy = NO_STRATEGY, bench_mode = 0
 │
 ▼  parse_args
 │    ├─ set_flag            --simple / --medium / --complex / --adaptive / --bench
 │    ├─ default             NO_STRATEGY → ADAPTIVE
 │    └─ per arg             ft_split → is_number → ft_atoi_overflow
 │                           → duplicate → node_new → stack_add_back
 │                                    │
 │                                    └── fail ──► ps_error
 │                                                 free stacks + split,
 │                                                 "Error" → stderr, exit 1
 ▼  indexing_stack           ranks 0..n-1 onto every node
 │
 ▼  compute_disorder         inversion ratio, BEFORE any move
 │
 ▼  is_sorted ? ──── yes ──► done, zero moves
 │        no
 ▼  run_strategy
 │    ├─ SIMPLE    → sort_simple
 │    ├─ MEDIUM    → sort_medium
 │    ├─ COMPLEX   → sort_complex
 │    └─ ADAPTIVE  → sort_adaptive ──┬─ disorder < 0.2 → selection
 │                                   ├─ disorder < 0.5 → chunks
 │                                   └─ else           → radix
 │                    │
 │                    ├─ n ≤ 3 → sort_small
 │                    │
 │                    └─ every move: ops_* ──► "ra\n" to stdout
 │                                         ├─► op_counter[OP_RA]++
 │                                         └─► total_ops++
 ▼  print_bench              no-op unless bench_mode; stderr only
 │
 ▼  stack_free × 2, return 0
```
 
Stack `b` is a staging buffer, never an output. Ordering gets established on the way in
so the trip back needs as few decisions as possible:
 
```
      stack a                                stack b
 ┌───────────────┐   pb + rotations   ┌────────────────────┐
 │ unsorted input│ ─────────────────► │ ordered descending │
 └───────────────┘                    │  (or near enough)  │
                                      └────────────────────┘
 ┌───────────────┐          pa                   │
 │ sorted output │ ◄────────────────────────────-┘
 └───────────────┘
```
 
All three strategies have this shape. They differ only in what they push and in what
order they pull back.
 
## Data structure
 
Doubly-linked list, explicit `bottom`, wrapped in a descriptor:
 
```c
typedef struct s_node {
    int value;  int index;
    struct s_node *next;  struct s_node *prev;
}   t_node;
 
typedef struct s_stack { t_node *top;  t_node *bottom;  int size; } t_stack;
typedef struct s_ps    { t_stack a;  t_stack b;  /* ... */ }        t_ps;
```
 
`prev` + `bottom` make `rra`/`rrb` and `stack_add_back` O(1). Singly-linked would walk
the list on every reverse rotation; an array would `memmove` on every rotation.
 
`index` holds the rank (0..n-1), not the value. Chunks and radix partition on rank, so
`-500, 3, 9999` become `0, 1, 2` and chunk boundaries stay even no matter how sparse the
input is.
 
`t_stack` sits inside `t_ps` by value. Its size is known at compile time — putting it on
the heap would buy two mallocs, two frees and two failure paths. Only nodes go on the
heap.
 
Both stacks are pre-sized by the input. Nothing allocates during sorting. Every move is
a pointer rewiring, never a copy.
 
## Disorder
 
`compute_disorder` counts inverted pairs over all n(n-1)/2 pairs. 0.0 is sorted, 1.0 is
reversed. Runs before any move, as the subject requires. Stored in `t_ps` so the router
and the benchmark read the same number instead of paying for a second O(n²) pass.
 
## Benchmark
 
Counters live in `t_ps` — globals are forbidden — and get bumped inside the move
wrappers. Printed total always equals emitted lines. `rr`, `ss` and `rrr` bump only
their own counter, never their components.
 
The percentage is formatted by scaling the double by 10000 and splitting into integer
and fractional parts. No `printf` float machinery, which keeps everything on `write` and
`ft_putnbr_fd` as the allowed-function list demands.
 
## Algorithms
 
Complexity here means **number of generated moves**, not classical array cost. Space is
auxiliary storage beyond the input.
 
### simple — selection sort — O(n²) time, O(n) space
 
Find the minimum in `a`, rotate it to the top, `pb`. Repeat. When `a` empties, `b` holds
everything descending, so `pa` × n gives ascending order with no extra logic.
 
Three refinements that cut the constant but not the class:
 
- **Shorter path.** Rotate `ra` if the minimum is in the upper half, `rra` otherwise.
  Average cost per element drops from m/2 to m/4.
- **Early exit.** After a rotation, if `a` is sorted, stop pushing — everything left in
  `a` is by construction larger than everything in `b`, so the remaining `pa`s finish it.
- **Base cases.** `sort_small` handles n ≤ 3 in at most two moves.
Iteration k works on n-k elements at an average rotation cost of (n-k)/4. Summing:
(1/4)·Σᵢ₌₁ⁿ i = n(n+1)/8 ≈ n²/8 rotations, plus 2n pushes.
 
Measured 1387 moves at n=100, 20889 at n=400. Matches n²/8 + 2n.
 
### medium — chunk sort — O(n√n) time, O(n) space
 
Split ranks into √n chunks. Walk `a`: element in the current chunk gets `pb`, anything
else gets rotated past. Elements from the lower half of a chunk take an extra `rb`,
which sinks them and leaves `b` roughly descending. Pull-back picks the cheapest element
to bring up and `pa`s it.
 
Each of the √n chunks costs at most one full traversal of `a` plus its own pushes:
√n · O(n) = O(n√n). `indexing_stack` writes ranks into existing nodes, so no auxiliary
array.
 
Fewer, larger chunks mean fewer traversals but sloppier ordering inside `b`. √n is the
balance point the subject prescribes.
 
### complex — binary radix, LSD — O(n log n) time, O(n) space
 
Keys are ranks, so the largest is n-1 and `max_bits = ⌈log₂ n⌉`. For each bit, low to
high: walk the stack once, `pb` if the bit is 0, `ra` if it's 1, then `pa` everything
back. Each pass is a stable partition on one bit. After `max_bits` passes the stack is
sorted.
 
⌈log₂ n⌉ passes × at most 2n moves each ≈ 2n·log₂ n. The two stacks *are* the buckets,
so no auxiliary storage.
 
**Why radix and not merge, quick, or a Fenwick tree.** The bottleneck isn't computing
where an element belongs — it's moving it there, with access only to the tops of two
stacks. A Binary Indexed Tree answers rank queries in O(log n) and does nothing about the
O(n) rotations needed to physically relocate an element. It would not deliver an
O(n log n) *move* bound. Radix is the one classical algorithm where every pass moves
every element closer to sorted using only the allowed instructions.
 
### adaptive — router
 
Thresholds come from the subject:
 
| Disorder | Method | Required | Delivered |
|---|---|---|---|
| < 0.2 | selection, early exit, base cases | O(n²) | O(n²) |
| 0.2 – 0.5 | chunks on √n | O(n√n) | O(n√n) |
| ≥ 0.5 | binary radix | O(n log n) | O(n log n) |
 
The ordering looks backwards. It isn't. A complexity class is an *upper* bound, not the
moves you actually pay. On a nearly-sorted stack the quadratic worst case never happens
— the early exit fires after a handful of rotations. Radix pays its fixed ⌈log₂ n⌉
passes over the whole stack regardless, which on almost-sorted input is pure waste. As
disorder climbs the situation flips and the stronger asymptotic guarantee wins. The
thresholds mark the crossovers.
 
Space is O(n) in every regime — stack `b` — plus O(1) working state.
 
## Numbers
 
| Input | Target: pass / good / excellent | Measured, default `--adaptive` |
|---|---|---|
| 100 random | < 2000 / < 1500 / < 700 | avg **805**, worst 1084 — good |
| 500 random | < 12000 / < 8000 / < 5500 | avg **6504**, worst 6784 — good |
 
Five runs per size, graded on the worst. A random permutation has expected disorder of
exactly 0.5 — every pair is inverted with probability ½ — so at n=500 the router lands
on either side of the high threshold from run to run. Chunks finish in 5539, radix in
6784. That's the entire gap between the averages.
 
Same input, n=500:
 
| Strategy | Moves |
|---|---|
| `--simple` | 33044 |
| `--medium` | 5539 |
| `--complex` | 6784 |
| `--adaptive` | 5539 |
 
### The classes, measured
 
Divide moves by each candidate function. The ratio that stops moving is the real class.
Five random inputs per size, averaged.
 
```
--simple                          --complex
   n      ops   ops/n²               n      ops   ops/(n·log₂n)
  25      126   0.2016              25      196   1.688
  50      424   0.1696              50      467   1.655
 100     1387   0.1387             100     1084   1.631
 200     5302   0.1325             200     2468   1.614
 400    20889   0.1305             400     5536   1.601
                ↓ 0.125 = 1/8      800    12272   1.591
```
 
`--simple` converges on 1/8, the exact constant from the n²/8 + 2n derivation. The
overshoot at small n is the linear 2n term — 40% of the total at n=25, 4% at n=400.
`--complex` flattens at ≈1.59·n·log₂n. As growth factors: doubling n multiplies moves by
3.93 for simple (theory 4.0) and 2.21 for complex (theory ≈2.2).
 
`--medium` measures *better* than its bound. The n√n ratio falls from 1.02 to 0.45 over
the same range and growth sits between 2.1 and 2.9 instead of the 2.83 a tight n^1.5
curve would give. Expected: O(n√n) is an upper bound, the worst case is real — √n
traversals of `a` — but on random input the `rb` heuristic keeps `b` close to ordered, so
pull-back costs far less than a full scan per element. The bound holds. It just isn't
tight here.
 
### Why the router exists
 
n=100, one adjacent pair swapped, disorder 0.05%:
 
| Strategy | Moves |
|---|---|
| `--simple` | **4** |
| `--medium` | 303 |
| `--complex` | 1084 |
| `--adaptive` | **4** |
 
Radix pays its ⌈log₂ n⌉ passes no matter how ordered the input already is. Selection
with an early exit stops after four moves. The router reads the disorder, picks the
quadratic method, and wins by 270×. That's the whole argument for the subject's
threshold ordering, in one table.
 
## Testing
 
 
```bash
shuf -i 0-9999 -n 100 > args.txt ; ./push_swap $(cat args.txt) | wc -l
shuf -i 0-9999 -n 500 > args.txt ; ./push_swap $(cat args.txt) | wc -l
 
# correctness of the same run
shuf -i 0-9999 -n 500 > args.txt ; ./push_swap $(cat args.txt) | ./checker_linux $(cat args.txt)
 
# which strategy actually ran
shuf -i 0-9999 -n 500 > args.txt ; ./push_swap --bench $(cat args.txt) 2> bench.txt \
    | ./checker_linux $(cat args.txt) ; cat bench.txt
 
# all four on identical input
shuf -i 0-9999 -n 500 > args.txt
for s in simple medium complex adaptive; do
    echo -n "$s: "; ./push_swap --$s $(cat args.txt) | wc -l
done
```
 
`valgrind --leak-check=full --show-leak-kinds=all` on every path, error paths included —
that's where partially built stacks and `ft_split` arrays hide.
## Contributions
 
| Learner | Areas |
|---|---|
| **kwlodars** | stack structure and node handling, argument parsing and validation, `pa`/`pb`, `sa`/`sb`/`ss`, chunk sort (`--medium`), testing and performance verification |
| **pkruszyn** | Makefile, `ra`/`rb`/`rr`, `rra`/`rrb`/`rrr`, selection sort (`--simple`), radix (`--complex`), adaptive router (`--adaptive`), benchmark mode (`--bench`) |
 
Both authors reviewed each other's code and can explain any part of the implementation.
 
## Resources
 
- Subject: `Push_swap`, 42 School
- A. Yigit Ogun, *Push Swap — A journey to find most efficient sorting algorithm*,
  Medium — the "Turk algorithm" <https://medium.com/@ayogun/push-swap-c1f5d2d41e97>;
- Big-O notation and amortised analysis: standard algorithm-complexity references
- 42 Norm (norminette) — coding standard applied to every file
- A. Y. Bhargava, *Grokking Algorithms* — accessible treatment of Big-O, sorting and divide-and-conquer

### Use of AI
 
An AI assistant (Claude) was used during development for the following tasks:
 
- **Design discussion** — trade-offs between a linked list and an array-based stack, between storing the stack descriptor by value or by pointer, and the choice of algorithm for each complexity class
- **Code review** — locating uninitialised variables, missing pointer rewirings in doubly-linked-list operations, memory leaks on error paths, Makefile issues and Norm violations
- **README.md** - editing the document
 