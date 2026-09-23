import torch
import transformers

from transformers import GPT2LMHeadModel, GPT2TokenizerFast

print("torch", torch.__version__, "| transformers", transformers.__version__)

# Tokenizer: Text <--> token IDs.
# Model: token IDs <--> next-token scores.
tok = GPT2TokenizerFast.from_pretrained("openai-community/gpt2")
model = GPT2LMHeadModel.from_pretrained("openai-community/gpt2").eval() # Eval = inference mode

ids = tok("The capital of France is", return_tensors = "pt").input_ids
print("token ids: ", ids.tolist())

with torch.no_grad():
    out = model.generate(ids, max_new_tokens=10, do_sample=False,
                         pad_token_id=tok.eos_token_id)

print("Generated: ", tok.decode(out[0]))
print("params: ", sum(p.numel() for p in model.parameters()))