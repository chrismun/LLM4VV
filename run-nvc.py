import os
import subprocess
import json

def compile_and_run_tests(test_dir, build_dir):
    results = {}

    # Create the build directory if it doesn't exist
    os.makedirs(build_dir, exist_ok=True)

    for filename in os.listdir(test_dir):
        if filename.endswith(".c"):
            test_name = os.path.splitext(filename)[0]
            test_path = os.path.join(test_dir, filename)
            build_path = os.path.join(build_dir, test_name)
            compile_command = f"nvc -I ~/Nvidia/OpenACCV-V/ -acc=gpu -Minfo=all {test_path} -o {build_path}"
            run_command = f"./{build_path}"

            # Compile the test
            print("Compiling:", filename)
            compile_result = subprocess.run(compile_command, shell=True, capture_output=True, text=True)
            compile_output = compile_result.stderr.strip()
            compile_exit_code = compile_result.returncode

            # Run the test and capture the exit code
            print("Running:", filename)
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

    return results

# Specify the path to the Tests folder
test_dir = "vvllm/gpt-4/oneshot_context/"

# Specify the path to the build directory
build_dir = "build"

# Specify the path to the result file
result_file = "gpt-4-one-shot-context.json"

# Compile and run the tests
test_results = compile_and_run_tests(test_dir, build_dir)

# Create the JSON output
output = {
    "runs": test_results
}

# Write the JSON output to the result file
with open(result_file, "w") as f:
    json.dump(output, f, indent=4)