#!/usr/bin/env bash
set -euo pipefail
mkdir -p models
BASE=https://huggingface.co/openai-community/gpt2/resolve/main
for f in model.safetensors vocab.json merges.txt; do
    curl -L -o "models/$f" "$BASE/$f"
done