def count_operations(file_path):
    # Initialize counters for each operation
    count_push = 0
    count_pop = 0
    count_write = 0
    count_read = 0

    # Open and read the file
    with open(file_path, 'r') as file:
        for line in file:
            if 'PUSH' in line:
                count_push += 1
            elif 'POP' in line:
                count_pop += 1
            elif 'WRITE' in line:
                count_write += 1
            elif 'READ' in line:
                count_read += 1

    # Print the counts
    print(f"PUSH: {count_push}")
    print(f"POP: {count_pop}")
    print(f"WRITE: {count_write}")
    print(f"READ: {count_read}")

# Use the function with a file path
count_operations('/Users/kirillzhukov/Documents/GitHub/Diplom/diplom/cmake-build-debug/default_log_file.txt')

