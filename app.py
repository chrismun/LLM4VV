import torch
from transformers import LlamaForCausalLM, LlamaTokenizer
import streamlit as st 
from flask import Flask, request, jsonify

app = Flask(__name__)

example_test = '''
#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copy(c[0:n])
    {
        #pragma acc parallel create(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - c[x]) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}
'''

context = '''
2486 2.12 Atomic Construct
2487 Summary
2488 An atomic construct ensures that a specific storage location is accessed and/or updated atomically,
2489 preventing simultaneous reading and writing by gangs, workers, and vector threads that could result
2490 in indeterminate values.
2491 Syntax
2492 In C and C++, the syntax of the atomic constructs is:
2493 #pragma acc atomic [ atomic-clause ] new-line
2494 expression-stmt
2495 or:
2496 #pragma acc atomic capture new-line
2497 structured block
2498 Where atomic-clause is one of read, write, update, or capture. The expression-stmt is an
2499 expression statement with one of the following forms:
2500 If the atomic-clause is read:
2501 v = x;
2502 If the atomic-clause is write:
2503 x = expr;
2504 If the atomic-clause is update or no clause appears:
2505 x++;
2506 x--;
2507 ++x;
2508 --x;
2509 x binop= expr;
2510 x = x binop expr;
2511 x = expr binop x;
2512 If the atomic-clause is capture:
2513 v = x++;
2514 v = x--;
2515 v = ++x;
2516 v = --x;
2517 v = x binop= expr;
2518 v = x = x binop expr;
2519 v = x = expr binop x;
2520 The structured-block is a structured block with one of the following forms:
69
The OpenACC
R API Version 3.3 2.12. Atomic Construct
2521 {v = x; x binop= expr;}
2522 {x binop= expr; v = x;}
2523 {v = x; x = x binop expr;}
2524 {v = x; x = expr binop x;}
2525 {x = x binop expr; v = x;}
2526 {x = expr binop x; v = x;}
2527 {v = x; x = expr;}
2528 {v = x; x++;}
2529 {v = x; ++x;}
2530 {++x; v = x;}
2531 {x++; v = x;}
2532 {v = x; x--;}
2533 {v = x; --x;}
2534 {--x; v = x;}
2535 {x--; v = x;}

'''

# Hugging Face model_path
model_path = 'psmathur/orca_mini_v2_13b'
tokenizer = LlamaTokenizer.from_pretrained(model_path)
model = LlamaForCausalLM.from_pretrained(
    model_path, torch_dtype=torch.float16, device_map='auto',
)

@app.route('/predict', methods=['POST'])
def predict():
    data = request.get_json(force=True)
    feature = data['text']

    system = 'You are an AI assistant that follows instruction extremely well. Help as much as you can. Only write code and explain it'
    
    prompt = f"### System:\n{system}\n\n### User:\n'Write a code in c following the example and context below to verify that a compiler is implementing the OpenACC {feature} correctly.\n\nContext: \n {context} \n Example Test: {example_test}\n\n### Response:\n"



    
    tokens = tokenizer.encode(prompt)
    tokens = torch.LongTensor(tokens).unsqueeze(0)
    tokens = tokens.to('cuda')

    instance = {'input_ids': tokens,'top_p': 1.0, 'temperature':0.7, 'generate_len': 1024, 'top_k': 50}

    length = len(tokens[0])
    with torch.no_grad():
        rest = model.generate(
            input_ids=tokens, 
            max_length=length+instance['generate_len'], 
            use_cache=True, 
            do_sample=True, 
            
            top_p=instance['top_p'],
            temperature=instance['temperature'],
            top_k=instance['top_k']
        )    
    output = rest[0][length:]
    string = tokenizer.decode(output, skip_special_tokens=True)
    # return f'[!] Response: {string}'
    return jsonify({'result': string})

if __name__ == '__main__':
    app.run(host='localhost', port=5000, debug=True)

# def main():
#     st.set_page_config(
#         page_title="UD LLMVV", page_icon=":bird:"
#     )

#     st.header("UD LLMVV :bird:")
#     feature = st.text_area("enter a feature to test")

#     if topic:
#         st.write("Generating test...")

#         result = generate_response(feature)

#         st.info(result)

# if __name__ == '__main__':
#     main()
