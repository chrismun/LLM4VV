import os
import subprocess
import json

def compile_and_run_tests(test_dir, build_dir):
    results = {}

    os.makedirs(build_dir, exist_ok=True)

    for filename in os.listdir(test_dir):
        compile_command = None
        base_name = os.path.splitext(filename)[0]
        test_name_for_json = f"{base_name}_{filename.split('.')[-1]}"
        if filename.endswith(".c"):
            test_name = f"{base_name}_c"
            test_path = os.path.join(test_dir, filename)
            build_path = os.path.join(build_dir, test_name)
            compile_command = f"nvc -acc -Minfo=all -o {build_path} {test_path}"
        elif filename.endswith(".cpp"):
            test_name = f"{base_name}_cpp"
            test_path = os.path.join(test_dir, filename)
            build_path = os.path.join(build_dir, test_name)
            compile_command = f"nvc++ -acc -Minfo=all -o {build_path} {test_path}"
        elif filename.endswith(".F90"):
            test_name = f"{base_name}_fortran"
            test_path = os.path.join(test_dir, filename)
            build_path = os.path.join(build_dir, test_name)
            compile_command = f"nvfortran -acc -Minfo=all -o {build_path} {test_path}"

        if not compile_command:
            continue

        run_command = f"./{build_path}"

        # Compile the test
        print("Compiling:", filename)
        compile_result = subprocess.run(compile_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        compile_output = compile_result.stderr.strip()
        compile_exit_code = compile_result.returncode

        # Run the test and capture the exit code
        print("Running:", filename)
        run_result = subprocess.run(run_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        run_output = run_result.stdout.strip()
        run_exit_code = run_result.returncode

        # Determine if the test passed or failed
        test_passed = run_exit_code == 0

        # Store the test result
        results[test_name_for_json] = {
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

test_dir = "../vvllm_git/gpt-4/template_context_full/"

build_dir = "build"

result_file = "results.json"

test_results = compile_and_run_tests(test_dir, build_dir)

output = {
    "runs": test_results
}

with open(result_file, "w") as f:
    json.dump(output, f, indent=4)