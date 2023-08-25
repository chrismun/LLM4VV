import torch
from transformers import AutoModelForCausalLM, AutoTokenizer, pipeline
from transformers import TrainingArguments, Trainer
import numpy as np
import evaluate
from datasets import load_dataset



tokenizer = AutoTokenizer.from_pretrained("upstage/Llama-2-70b-instruct", torch_dtype=torch.float16, low_cpu_mem_usage=True, device_map="auto")
model = AutoModelForCausalLM.from_pretrained("upstage/Llama-2-70b-instruct")

training_args = TrainingArguments(output_dir="test_trainer")

metric = evaluate.load("accuracy")

def compute_metrics(eval_pred):
    logits, labels = eval_pred
    predictions = np.argmax(logits, axis=-1)
    return metric.compute(predictions=predictions, references=labels)

training_args = TrainingArguments(output_dir="test_trainer", evaluation_strategy="epoch")

dataset = load_dataset("text", data_files={"train": "train.txt", "test": "test.txt"})

def tokenize_function(examples):
    return tokenizer(examples["text"], padding="max_length", truncation=True)

tokenized_datasets = dataset.map(tokenize_function, batched=True)

trainer = Trainer(
    model=model,
    args=training_args,
    train_dataset=tokenized_datasets["train"],
    eval_dataset=tokenized_datasets["test"],
    compute_metrics=compute_metrics,
)

trainer.train()


