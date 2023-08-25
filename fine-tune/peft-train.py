from peft import LoraConfig, TaskType
from peft import get_peft_model
from transformers import LlamaForCausalLM, LlamaTokenizer, DataCollatorForLanguageModeling
from transformers import AutoModelForCausalLM, AutoTokenizer
from datasets import concatenate_datasets, load_dataset
import torch
import numpy as np
import os
import time
import datetime
from transformers import Trainer, TrainingArguments

# Dataset 
# Format: System,User,Assistant

dataset = load_dataset("csv", data_files={"train": "train.csv", "test": "test.csv"})

print(f"Train dataset size: {len(dataset['train'])}")
print(f"Test dataset size: {len(dataset['test'])}")


# PeftConfig
peft_config = LoraConfig(task_type=TaskType.CAUSAL_LM, target_modules=["Assistant"], inference_mode=False, r=8, lora_alpha=32, lora_dropout=0.1)

# PeftModel
checkpoint = "Salesforce/codegen-350M-mono"
model = AutoModelForCausalLM.from_pretrained(checkpoint)
tokenizer = AutoTokenizer.from_pretrained(checkpoint)
# model_path = 'psmathur/orca_mini_v2_13b'
# tokenizer = LlamaTokenizer.from_pretrained(model_path)
# model = LlamaForCausalLM.from_pretrained(
#     model_path, torch_dtype=torch.float16, device_map='auto',
# )

model = get_peft_model(model, peft_config)
model.print_trainable_parameters()


# Preprocess
tokenized_inputs = concatenate_datasets([dataset["train"], dataset["test"]]).map(lambda x: tokenizer(x["System"] + x["User"], truncation=True), batched=True, remove_columns=["System", "User", "Assistant"])
input_lengths = [len(x) for x in tokenized_inputs["input_ids"]]

max_source_length = int(np.percentile(input_lengths, 85))
print(f"Max source length: {max_source_length}")

tokenized_targets = concatenate_datasets([dataset["train"], dataset["test"]]).map(lambda x: tokenizer(x["Assistant"], truncation=True), batched=True, remove_columns=["System", "User", "Assistant"])
target_lengths = [len(x) for x in tokenized_targets["input_ids"]]
max_target_length = int(np.percentile(target_lengths, 90))
print(f"Max target length: {max_target_length}")

def preprocess_function(sample,padding="max_length"):
    # inputs = [x["System"] + "\n" + x["User"] for x in sample["User"]]

    model_inputs = tokenizer(sample["User"], max_length=max_source_length, padding=padding, truncation=True)

    labels = tokenizer(sample["Assistant"], max_length=max_target_length, padding=padding, truncation=True)

    # If we are padding here, replace all tokenizer.pad_token_id in the labels by -100 when we want to ignore
    # padding in the loss. (? cm)
    if padding == "max_length":
        labels["input_ids"] = [
            [(l if l != tokenizer.pad_token_id else -100) for l in label] for label in labels["input_ids"]
        ]

    model_inputs["labels"] = labels["input_ids"]
    return model_inputs

tokenized_dataset = dataset.map(preprocess_function, batched=True, remove_columns=["System", "User", "Assistant"])

print(f"Keys of tokenized dataset: {list(tokenized_dataset['train'].features)}")


# Data Collater
# we want to ignore tokenizer pad token in the loss
label_pad_token_id = -100

data_collator = DataCollatorForLanguageModeling(
    tokenizer,
    pad_to_multiple_of=8,
    mlm=False,

)

# Hyperparameters

output_dir="lora-flan-t5-xxl"

# Define training args
training_args = TrainingArguments(
    output_dir=output_dir,
    auto_find_batch_size=True,
    learning_rate=1e-3, # higher learning rate
    num_train_epochs=5,
    logging_dir=f"{output_dir}/logs",
    logging_strategy="steps",
    logging_steps=500,
    save_strategy="no",
    report_to="tensorboard",
)

# Create Trainer instance
trainer = Trainer(
    model=model,
    args=training_args,
    data_collator=data_collator,
    train_dataset=tokenized_dataset["train"],
)
model.config.use_cache = False  # silence the warnings. Please re-enable for inference!

model.config.use_cache = False  # silence the warnings. Please re-enable for inference!

# train model
trainer.train()

# Save our LoRA model & tokenizer results
peft_model_id="results"
trainer.model.save_pretrained(peft_model_id)
tokenizer.save_pretrained(peft_model_id)

# https://www.philschmid.de/fine-tune-flan-t5-peft