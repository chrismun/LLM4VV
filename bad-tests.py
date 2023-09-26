import os
import shutil
import json

# Path to the directory containing all test directories
tests_directory = "vvllm"

# Path to the results directory
results_directory = "results"

# Path to the folder where failed tests will be copied
failed_tests_folder = "vvllm/bad-tests-v2"

# Create the failed tests folder if it doesn't exist
os.makedirs(failed_tests_folder, exist_ok=True)

# Counter for the number of tests copied
tests_copied = 0

# Iterate over the result files
for result_file in os.listdir(results_directory):
    if result_file.endswith(".json"):
        # Read the JSON file
        with open(os.path.join(results_directory, result_file), "r") as file:
            data = json.load(file)

        # Determine the test directory from the result file name
        test_subdirectory = result_file.replace("vvllm_", "").replace("_", "/").replace(".json", "")

        # Iterate over the tests
        for test_name, test_data in data["runs"].items():
            # Remove the file extension from the test name
            test_name_no_ext, file_extension = os.path.splitext(test_name)

            # Check if the 'execution' key exists
            if test_name_no_ext in test_data and "execution" in test_data[test_name_no_ext]:
                # Check if the test failed
                if not test_data[test_name_no_ext]["execution"]["passed"]:
                    # Get the test file name from the compilation command
                    compilation_command = test_data[test_name_no_ext]["compilation"]["command"]
                    test_file = compilation_command.split()[-1].split("/")[-1]
                    
                    # Add the file extension back to the test file name
                    test_file += file_extension

                    # Copy the test file to the failed tests folder
                    file_path = os.path.join(tests_directory, test_subdirectory, test_file)
                    dest_path = os.path.join(failed_tests_folder, test_file)

                    if os.path.isfile(file_path):
                        version = 1
                        while os.path.exists(dest_path):
                            base, ext = os.path.splitext(test_file)
                            dest_path = os.path.join(failed_tests_folder, f"{base}_v{version}{ext}")
                            version += 1

                        print(f"Copying {file_path} to {dest_path}")
                        shutil.copy(file_path, dest_path)
                        tests_copied += 1
                    else:
                        print(f"File {file_path} does not exist")
                else:
                    print(f"Test {test_name} passed")
            else:
                print(f"'execution' key not found in test data for {test_name}")

print(f"Finished copying files. Total tests copied: {tests_copied}")