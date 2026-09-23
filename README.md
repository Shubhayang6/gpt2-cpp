# gpt2-cpp

From-scratch GPT-2 small (124M) inference engine in C++17 + CUDA. No ML frameworks at runtime.
Every step is validated against PyTorch.

## Status
M1 — CPU forward pass: in progress

## Benchmarks
| Milestone | Backend | ms/token | tokens/s | Peak mem | Max logit diff vs PyTorch |
|---|---|---|---|---|---|

## Build
cmake -S . -B build
cmake --build build --config Release

## Python Build
## Python reference (validation only)
```
py -3.12 -m venv .venv
.\.venv\Scripts\Activate.ps1
pip install torch --index-url https://download.pytorch.org/whl/cpu
pip install -r scripts/requirements.txt
```