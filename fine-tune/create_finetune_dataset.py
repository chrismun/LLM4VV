import os
import random

def create_dataset(directory, train_file, test_file):
    # Ensure the directory exists
    if not os.path.exists(directory):
        print(f"Directory {directory} does not exist!")
        return

    # Collect all .c filenames
    c_files = [filename for filename in os.listdir(directory) if filename.endswith('.c')]
    # Shuffle the list
    random.shuffle(c_files)

    # Split the list into training and testing sets
    split_idx = int(0.8 * len(c_files))
    train_files = c_files[:split_idx]
    test_files = c_files[split_idx:]

    # Helper function to write to a file
    def write_to_file(filenames, output_file):
        with open(output_file, 'w') as out_file:
            for filename in filenames:
                filepath = os.path.join(directory, filename)
                with open(filepath, 'r') as file:
                    file_contents = file.read().replace('\n', ' ')  # Remove newlines from file contents
                    # Write the formatted content to the output file
                    out_file.write(f"### System : You will help create tests. ### User : Create a test for the feature {filename} ### Assistant : {file_contents} ")

    # Write to the train and test files
    write_to_file(train_files, train_file)
    write_to_file(test_files, test_file)

if __name__ == "__main__":
    directory = input("Enter the directory path: ")
    train_file = "train.txt"
    test_file = "test.txt"
    create_dataset(directory, train_file, test_file)
    print(f"Training dataset created in {train_file}!")
    print(f"Testing dataset created in {test_file}!")
