import os
import torch
import tempfile
from transformers import LlamaForCausalLM, LlamaTokenizer

from langchain.embeddings import HuggingFaceEmbeddings
from langchain.text_splitter import CharacterTextSplitter
from langchain.vectorstores import SKLearnVectorStore
from langchain.document_loaders import TextLoader

# Hugging Face model
model_path = 'psmathur/orca_mini_v2_13b'
tokenizer = LlamaTokenizer.from_pretrained(model_path)
model = LlamaForCausalLM.from_pretrained(
    model_path, torch_dtype=torch.float16, device_map='auto',
)

# Lanchain vector db 
loader = TextLoader("data/spec.txt")
documents = loader.load()
text_splitter = CharacterTextSplitter(chunk_size=1000, chunk_overlap=100)
docs = text_splitter.split_documents(documents)
embeddings = HuggingFaceEmbeddings()
persist_path = os.path.join(tempfile.gettempdir(), "union.parquet")
vector_store = SKLearnVectorStore.from_documents(
    documents=docs,
    embedding=embeddings,
    persist_path=persist_path,  # persist_path and serializer are optional
    serializer="parquet",
)


# Generate text function
def generate_text(system, instruction, input=None):
    if input:
        prompt = f"### System:\n{system}\n\n### User:\n{instruction}\n\n### Input:\n{input}\n\n### Response:\n"
    else:
        prompt = f"### System:\n{system}\n\n### User:\n{instruction}\n\n### Response:\n"
    
    tokens = tokenizer.encode(prompt)
    tokens = torch.LongTensor(tokens).unsqueeze(0)
    tokens = tokens.to('cuda')

    instance = {'input_ids': tokens, 'top_p': 1.0, 'temperature': 0.4, 'generate_len': 1024, 'top_k': 50}

    length = len(tokens[0])
    with torch.no_grad():
        rest = model.generate(
            input_ids=tokens, 
            max_length=length + instance['generate_len'], 
            use_cache=True, 
            do_sample=True, 
            top_p=instance['top_p'],
            temperature=instance['temperature'],
            top_k=instance['top_k']
        )    
    output = rest[0][length:]
    string = tokenizer.decode(output, skip_special_tokens=True)
    return f'[!] Response: {string}'

# Prompt for OpenACC Compiler Implementation Validation

# Example Test
example_test = '''
### Example Test: 

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
    }

    #pragma acc data copyin(a[0:n]) copy(b[0:n], c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif
'''

# Task
task = '''
# Task:

Write a C code snippet that utilizes OpenACC to perform a specific computation 
or operation. Ensure the code involves features relevant to the OpenACC specification that you are
asked to validate. Please refer to the given example test and the context above as you write the code.
Follow the format of the code above, by declaring some arrays, performing operations on them using 
the feature being tested, and returning an error code if the feature is not implemented correctly.
'''

# Combine the instructions

features = [
    "Parallel Construct",
    "Serial Construct",
    "Kernels Construct",
    "if clause",
    "self clause",
    "async clause",
    "wait clause",
    "num gangs clause",
    "num workers clause",
    "vector length clause",
    "private clause",
    "firstprivate clause",
    "reduction clause",
    "default clause",
    "Variables with Predetermined Data Attributes",
    "Variables with Implicitly Determined Data Attributes",
    "Data Regions and Data Lifetimes",
    "Data Structures with Pointers",
    "Data Construct",
    "Enter Data and Exit Data Directives",
    "Reference Counters",
    "Attachment Counter",
    "Data Clauses",
    "Data Specification in Data Clauses",
    "Data Clause Actions",
    "Data Clause Errors",
    "deviceptr clause",
    "present clause",
    "copy clause",
    "copyin clause",
    "copyout clause",
    "create clause",
    "no create clause",
    "delete clause",
    "attach clause",
    "detach clause",
    "Host Data Construct",
    "use device clause",
    "if clause",
    "if present clause",
    "Loop Construct",
    "collapse clause",
    "gang clause",
    "worker clause",
    "vector clause",
    "seq clause",
    "independent clause",
    "auto clause",
    "tile clause",
    "device type clause",
    "private clause",
    "reduction clause",
    "Cache Directive",
    "Combined Constructs",
    "Atomic Construct",
    "Declare Directive",
    "device resident clause",
    "create clause",
    "link clause",
    "Executable Directives",
    "Init Directive",
    "Shutdown Directive",
    "Set Directive",
    "Update Directive",
    "Wait Directive",
    "Enter Data Directive",
    "Exit Data Directive",
    "Procedure Calls in Compute Regions",
    "Routine Directive",
    "Global Data Access",
    "Asynchronous Behavior",
    "async clause",
    "wait clause",
    "Wait Directive",
    "Fortran Specific Behavior",
    "Do Concurrent Construct",
    "acc get num devices",
    "acc set device type",
    "acc get device type",
    "acc set device num",
    "acc get device num",
    "acc get property",
    "acc init",
    "acc shutdown",
    "acc async test",
    "acc wait",
    "acc wait async",
    "acc wait any",
    "acc get default async",
    "acc set default async",
    "acc on device",
    "acc malloc",
    "acc free",
    "acc copyin and acc create",
    "acc copyout and acc delete",
    "acc update device and acc update self",
    "acc map data",
    "acc unmap data",
    "acc deviceptr",
    "acc hostptr",
    "acc is present",
    "acc memcpy to device",
    "acc memcpy from device",
    "acc memcpy device",    "acc init",
    "acc shutdown",
    "acc async test",
    "acc wait",
    "acc wait async",
    "acc wait any",
    "acc get default async",
    "acc set default async",
    "acc on device",
    "acc malloc",
    "acc free",
    "acc copyin and acc create",
    "acc copyout and acc delete",
    "acc update device and acc update self",
    "acc map data",
    "acc unmap data",
    "acc deviceptr",
    "acc hostptr",
    "acc is present",
    "acc memcpy to device",
    "acc memcpy from device",
    "acc memcpy device",
    "acc attach and acc detach",
    "acc memcpy d2d"
]
system = 'You are an AI assistant that follows instruction extremely well. Help as much as you can. You will write code to validate compiler implementations of OpenACC specification.'

for feature in features[8:10]:
    context = vector_store.similarity_search(feature)
    context = context[0].page_content
    instruction = example_test + context + task + f"Write a C code using the example test and context above to test that a compiler is implementing the OpenACC {feature} correctly. Make sure to use the specified feature. Follow the general format of the example, but don't copy it." 
    print(f"debug: instruction = {instruction}")
    print(generate_text(system, instruction))
