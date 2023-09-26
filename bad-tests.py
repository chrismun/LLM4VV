import os
import shutil
import json

# Path to the JSON file
json_file = "vvllm/results/gpt-4-template-context-full.json"

# Path to the folder containing all the tests
all_tests_folder = "vvllm/gpt-4/template_context_full"

# Path to the folder where failed tests will be copied
failed_tests_folder = "vvllm/bad-tests"


# Read the JSON file
with open(json_file, "r") as file:
    data = json.load(file)

# Iterate over the tests
for test_name, test_data in data["runs"].items():
    # Check if the test failed
    if not test_data["execution"]["passed"]:
        # Get the test file name from the compilation command
        compilation_command = test_data["compilation"]["command"]
        test_file = compilation_command.split()[-1].split("/")[-1]
        
        # Copy the test file to the failed tests folder
        file_path = os.path.join(all_tests_folder, test_file)
        if os.path.isfile(file_path):
            print(f"Copying {file_path} to {failed_tests_folder}")
            shutil.copy(file_path, failed_tests_folder)
        else:
            print(f"File {file_path} does not exist")
    else:
        print(f"Test {test_name} passed")

print("Finished copying files")