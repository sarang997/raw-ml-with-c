# raw-ml-with-c

Building ML fundamentals from scratch in C — no frameworks, no autograd,
just pointers and flat arrays. Working toward implementing GPT-2 
forward/backward passes in raw C (à la Karpathy's llm.c).

## Structure
- `pointers/` — pass-by-value vs pass-by-pointer, array decay
- `memory/` — malloc/calloc/free/realloc fundamentals
- `matrix-ops/` — flat-array 2D/3D indexing, matmul, transpose
- ...

## Why
Most ML work happens at the PyTorch/numpy layer. This is the layer underneath —
understanding what a tensor actually *is* in memory, and how the operations
on it actually get computed.
