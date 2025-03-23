import subprocess
import numpy as np
import sys
import os
import matplotlib.pyplot as plt

epsilon = 1e-7
executable = "./build/integrate_parallel"
num_functions = 3
output_dir = "execution_results"

os.makedirs(output_dir, exist_ok=True)

if len(sys.argv) < 2:
    print("Usage: python run_cuda_integration.py <num_runs> <threads_quantity> [p]")
    sys.exit(1)

num_runs = int(sys.argv[1])
selected_threads = [int(sys.argv[2])] if len(sys.argv) < 4 else list(range(1,17)) + [100,1000]

data_files = [os.path.join(output_dir, f"parallel_data_func{func}.txt") for func in range(1, num_functions + 1)]
graph_files = [os.path.join(output_dir, f"parallel_plot_func{func}.png") for func in range(1, num_functions + 1)]

for func_number in range(1, num_functions + 1):
    config_file = f"func{func_number}.cfg"
    results = []

    for threads in selected_threads:
        times = []
        for _ in range(num_runs):
            process = subprocess.Popen([executable, str(func_number), config_file, str(threads)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = process.communicate()

            if process.returncode != 0:
                print(f"Error executing function {func_number} with {threads} threads: {stderr.decode().strip()}")
                continue

            output_lines = stdout.decode().strip().split("\n")
            if len(output_lines) < 4:
                print(f"Unexpected output for function {func_number} with {threads} threads")
                continue

            execute_time = float(output_lines[3])
            times.append(execute_time)

        if times:
            min_time = min(times)
            mean_time = np.mean(times)
            std_dev = np.std(times, ddof=1)
            results.append(f"{threads} {min_time:.6f} {mean_time:.6f} {std_dev:.6f}\n")
            print(f"Function {func_number}, Threads {threads}: Min {min_time:.6f} ms, Mean {mean_time:.6f} ms, Std Dev {std_dev:.6f} ms")

    with open(data_files[func_number - 1], "w") as f:
        f.writelines(results)

if len(sys.argv) > 3 and sys.argv[3] == 'p':
    for func_number in range(1, num_functions + 1):
        execution_times = {}
        try:
            with open(data_files[func_number - 1], "r") as f:
                for line in f.readlines():
                    parts = line.strip().split()
                    if len(parts) == 4:
                        execution_times[int(parts[0])] = float(parts[2])

        except FileNotFoundError:
            print(f"No data found for function {func_number}, skipping graph generation.")
            continue

        if execution_times:
            sorted_threads = sorted(execution_times.keys())
            times = [execution_times[t] for t in sorted(execution_times.keys())]
            thread_labels = [str(t) for t in sorted_threads]
            x_positions = np.arange(len(sorted_threads))

            plt.figure(figsize=(8, 5))
            plt.bar(thread_labels, times, color='blue', width=0.6)
            plt.xlabel("Number of Threads")
            plt.ylabel("Execution Time (ms)")
            plt.title(f"Execution Time vs Threads - Function {func_number}")
            plt.grid(True)
            plt.savefig(graph_files[func_number - 1])
            plt.close()
            print(f"Graph saved as {graph_files[func_number - 1]}")


            plt.figure(figsize=(10, 5))
            plt.plot(x_positions, times, marker='o', linestyle='-', color='b', label=f"Function {func_number}")
            plt.xticks(x_positions, sorted_threads)
            plt.xlabel("Number of Threads")
            plt.ylabel("Execution Time (ms)")
            plt.yscale("log")
            plt.title(f"Execution Time vs Threads (Log Scale) - Function {func_number}")
            plt.legend()
            plt.grid(True)
            plt.savefig(graph_files[func_number - 1].replace(".png", "_log.png"))
            plt.close()
            print(f"Log graph saved as {graph_files[func_number - 1].replace('.png', '_log.png')}")
