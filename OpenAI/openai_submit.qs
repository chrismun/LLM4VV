#!/bin/bash -l
#SBATCH --nodes=1
#SBATCH --mem=64G
#SBATCH --job-name=llmvv-oai
#SBATCH --partition=gpu-t4
#SBATCH --gpus=1
#SBATCH --time=02:00:00
#SBATCH --output=%x-%j.out
#SBATCH --error=%x-%j.err
#SBATCH --export=NONE

vpkg_require anaconda/2023.03:python3
conda activate /lustre/schandra_crpl/sw/anaconda-envs/tmp
export HF_HOME="/lustre/schandra_crpl/users/2802/.cache"
export HUGGINGFACE_HUB_CACHE="/lustre/schandra_crpl/users/2802/.cache"

# List of OpenACC features
declare -a features=("parallel construct with copyout clause"
                     "data clause"
                     "kernels directive"
                     "loop directive"
                     # Add more features as needed
                    )

for feature in "${features[@]}"; do
    response=$(curl -s https://api.openai.com/v1/chat/completions \
               -H "Content-Type: application/json" \
               -H "Authorization: Bearer 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" \
               -d "{
                   \"model\": \"gpt-3.5\",
                   \"messages\": [{\"role\": \"user\", \"content\": \"Write a C code to test OpenACC compiler implementation of the $feature\"}],
                   \"temperature\": 0.7
                  }")
    
    # Process the response if needed (like saving to a file or printing)
    echo "$response"
done


# #!/bin/bash -l
# #SBATCH --nodes=1
# #SBATCH --mem=64G
# #SBATCH --job-name=llmvv-oai
# #SBATCH --partition=gpu-v100
# #SBATCH --gpus=1
# #SBATCH --time=02:00:00
# #SBATCH --output=%x-%j.out
# #SBATCH --error=%x-%j.err
# #SBATCH --export=NONE

# vpkg_require anaconda/2023.03:python3
# conda activate /lustre/schandra_crpl/sw/anaconda-envs/tmp
# export HF_HOME="/lustre/schandra_crpl/users/2802/.cache"
# export HUGGINGFACE_HUB_CACHE="/lustre/schandra_crpl/users/2802/.cache"

# # python3 src/inference_wizardcoder.py --base_model "WizardLM/WizardCoder-15B-V1.0" --input_data_path "prooompts_noExample2.jl" --output_data_path "output_noEx2.jl" 
# # python3 fine-tune/sft_trainer.py --load_in_4bit=True --use_peft=True --model_name='psmathur/orca_mini_v2_13b' 
# curl https://api.openai.com/v1/chat/completions \
#   -H "Content-Type: application/json" \
#   -H "Authorization: Bearer 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" \
#   -d '{
#      "model": "gpt-4",
#      "messages": [{"role": "user", "content": "Write a C code to test OpenACC compiler implementation of the parallel construct with copyout clause"}],
#      "temperature": 0.7
#    }'