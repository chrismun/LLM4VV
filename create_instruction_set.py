import os
import tempfile
import json 
from langchain.embeddings import HuggingFaceEmbeddings
from langchain.text_splitter import CharacterTextSplitter
from langchain.vectorstores import SKLearnVectorStore
from langchain.document_loaders import TextLoader



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

# Prompt for OpenACC Compiler Implementation Validation

# Example Test
example_test = '''#include "acc_testsuite.h"
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

idx = 1

prooompts = []

for feature in features:
    context = vector_store.similarity_search(feature)
    context = "\nOpenACC specification:\n" + context[0].page_content
    # instruction = example_test + context + f"Write a C code using the example output and the specification above to test that a compiler is implementing the OpenACC {feature} correctly. Make sure to use the specified feature and follow the format of the provided example." 
    instruction = "Example Test:\n" + example_test + context + f"Write a C code to test that time compiler is impleneting the OpenACC {feature} correctly using the specification and example code above."
    # instruction = f"Write a C code to test that the compiler is implementing the OpenACC {feature} correctly." 
    tmp = {
        "idx": idx,
        "Instruction": instruction
    }
    prooompts.append(tmp)
    idx += 1

with open('prooompts.json', 'w') as f:
    for entry in prooompts:
        f.write(json.dumps(entry) + '\n')