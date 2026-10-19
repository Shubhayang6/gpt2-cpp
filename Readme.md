# gpt2-cpp

From-scratch GPT-2 small (124M) inference engine in C++17, then CUDA.
No ML framework at runtime. Every step is checked against PyTorch.

## Status
Phase 1 — CPU forward pass: in progress

## Benchmarks
| Phase | Device | ms/token | tokens/s | Peak memory | Max diff vs PyTorch |
|---|---|---|---|---|---|

## Build
Windows: `cmake -S . -B build` then `cmake --build build --config Release`
Linux:   `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release` then `cmake --build build`

## Python answer key (validation only)
python -m venv .venv, activate, `pip install -r scripts/requirements.txt`