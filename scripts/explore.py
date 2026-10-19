import torch
from transformers import GPT2LMHeadModel, GPT2TokenizerFast

tok = GPT2TokenizerFast.from_pretrained("openai-community/gpt2")
model = GPT2LMHeadModel.from_pretrained("openai-community/gpt2").eval()

ids = tok("The capital of France is").input_ids   # text -> list of ints

for i in ids:                                      # see what each ID is
    print(f"{i:>6}  {tok.decode([i])!r}")          # !r shows the leading spaces

for _ in range(10):
    with torch.no_grad():
        logits = model(torch.tensor([ids])).logits # [1, T, 50257]: a score per vocab word
    next_id = int(logits[0, -1].argmax())          # last position, highest score
    ids.append(next_id)                            # feed it back in

print("greedy:", tok.decode(ids))