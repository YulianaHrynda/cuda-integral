# Lab work 3: Parallel Integral
Authors (team):\
Pavlosiuk Roman - https://github.com/UCUgllekk \
Hrynda Yuliana - https://github.com/YulianaHrynda \
Denysova Iryna - https://github.com/Shnapa

## Prerequisites

Boost\
G++ or Clang++\
CMake >= 1.15\
Python >= 3.11

### Compilation

To compile the whole program, follow these steps:

Create a build directory and go there
```sh
mkdir -p build && cd build
```
Run cmake to generate build files
```sh
cmake ..
```
Compile the project
```sh
cmake --build .
```

#### Running
To run the compiled executables (depending on what do you need)
```sh
./integrate_parallel method_number cfg_file_path number_of_threads
```
Range of number of threads are: [ 1, 2, 4, 8, 16, 100, 1000]

#### Function numbers:
- `func_1 ( Де Джонга )` - 1
- `func_2 ( Ackley's )` - 2
- `func_3 ( Langermann )` - 3
- `func_4 ( Additional )` - 4


### Installation

In order to use python scripts, use
```sh
pip install -r dependencies/requirements.txt
```

### Usage

For configurations for functions, you can just use func[1-4].cfg files to get parameters

In order to run python script to get more data, just run:
```sh
python3 run_cuda_integration.py <num_runs> <num of threads> 
```
If you want to see the plots of the runs on different thread quantity:
```sh
python3 run_cuda_integration.py <num_runs> <num of threads> <p>
```
Here the num of threads does not matter, because if the "p" flag is in the code, it will use the list of the different threads quantity for the correct plot generation

And also there is the file which compares the time results of our previous and this lab integral calculations in order to run it, use this:
```sh
python3 effect.py
```


 ### Mutex and Atomic synchronizations
In order to run mutex implementation run:
```sh
./mutex_integration method_number cfg_file_path number_of_threads
```

Similarly for atomic implementation:
```sh
./atomic_integration method_number cfg_file_path number_of_threads
```
 

### Results

In this Lab we finally worked with parallel computing. Learnt different styles of synchronization (mutex, atomic variable, saving into array).
Also compared results how number of threads to run program shows on different computers. Also it was strange that even first number (2 in 200, 3 in 300 etc.) of threads is always better in performance in like 3-4 times then odd.
Like 200 threads is much faster than 300, and 600 is much faster than 700

# Additional tasks

* Run files on different laptops to compare results with different number of threads
* Program with std::mutex, std::atomic


