@echo off
if not exist models mkdir models
set BASE=https://huggingface.co/openai-community/gpt2/resolve/main
curl -L -o models\model.safetensors %BASE%/model.safetensors
curl -L -o models\vocab.json        %BASE%/vocab.json
curl -L -o models\merges.txt        %BASE%/merges.txt
@REM Vocab and merges are the tokenizer files