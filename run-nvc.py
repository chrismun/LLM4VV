import os
import subprocess
import json

def compile_and_run_tests(test_file, build_dir):
    results = {}

    # Create the build directory if it doesn't exist
    os.makedirs(build_dir, exist_ok=True)

    # Convert the file extension to lowercase before checking it
    if test_file.lower().endswith((".c", ".cpp", ".f90")):
        test_name = os.path.splitext(os.path.basename(test_file))[0]
        build_path = os.path.join(build_dir, test_name)
        compile_command = f"nvc -I ~/Nvidia/OpenACCV-V/ -acc=gpu -Minfo=all {test_file} -o {build_path}"
        run_command = f"./{build_path}"

        # Compile the test
        print("Compiling:", test_file)
        compile_result = subprocess.run(compile_command, shell=True, capture_output=True, text=True)
        compile_output = compile_result.stderr.strip()
        compile_exit_code = compile_result.returncode

        # Run the test and capture the exit code
        print("Running:", test_file)
        run_result = subprocess.run(run_command, shell=True, capture_output=True, text=True)
        run_output = run_result.stdout.strip()
        run_exit_code = run_result.returncode

        # Determine if the test passed or failed
        test_passed = run_exit_code == 0

        # Store the test result
        results[test_name] = {
            "compilation": {
                "command": compile_command,
                "output": compile_output,
                "exit_code": compile_exit_code
            },
            "execution": {
                "command": run_command,
                "output": run_output,
                "exit_code": run_exit_code,
                "passed": test_passed
            }
        }

    return results# Check if the test file is not empty


# Specify the path to the directory containing all test directories
tests_directory = "vvllm"

# Specify the path to the build directory
build_dir = "build"

# Specify the path to the result directory
result_dir = "results"
os.makedirs(result_dir, exist_ok=True)

# Specify the directories to ignore
ignore_dirs = ['headers', 'results', 'bad-tests', 'bad-tests-v2', '.git']

# Iterate over the test directories
for root, dirs, files in os.walk(tests_directory):
    # Ignore specified directories
    dirs[:] = [d for d in dirs if d not in ignore_dirs]

    # Initialize a dictionary to store the results of all tests in the current directory
    all_test_results = {}

    for filename in files:
        # Convert the file extension to lowercase before checking it
        if filename.lower().endswith((".c", ".cpp", ".f90")):
            test_path = os.path.join(root, filename)
            build_path = os.path.join(build_dir, os.path.splitext(filename)[0])

            # Compile and run the test
            test_results = compile_and_run_tests(test_path, build_path)

            # Add the test results to the dictionary
            all_test_results[filename] = test_results

    # Only create a .json file if there were any test files in the directory
    if all_test_results:
        # Replace slashes in the root path with underscores for the result file name
        result_file_name = root.replace('/', '_') + ".json"
        result_file = os.path.join(result_dir, result_file_name)

        # Create the JSON output
        output = {
            "runs": all_test_results
        }

        # Write the JSON output to the result file
        with open(result_file, "w") as f:
            json.dump(output, f, indent=4)