# gpt2-cpp

From-scratch GPT-2 small (124M) inference engine in C++17 + CUDA. No ML Frameworks at runtime

Goal: correctness validated against PyTorch, with benchmark numbers for each optimization.

## Status
Milestone-1 - safetensors loader + CPU forward pass: in progress

## Benchmarks (T4, Colab)
| Milestone | Backend | ms/token | tokens/s | Peak memory | Max logit diff vs PyTorch |
|---|---|---|---|---|---|
|To-Do|To-Do|To-Do|To-Do|To-Do|To-Do|
|To-Do|To-Do|To-Do|To-Do|To-Do|To-Do|

## Build
`cmake -B build`<br>
`cmake --build build`<br>

