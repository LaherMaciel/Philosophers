# 🍽️ Philosophers - Dining Philosophers Problem

[![42 School](https://img.shields.io/badge/42-School-blue.svg)](https://42.fr/)
[![C](https://img.shields.io/badge/Language-C-green.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Pthreads](https://img.shields.io/badge/Threading-Pthreads-orange.svg)](https://man7.org/linux/man-pages/man7/pthreads.7.html)
[![Norminette](https://img.shields.io/badge/Code%20Style-Norminette-red.svg)](https://github.com/42School/norminette)
[![License](https://img.shields.io/badge/License-42%20School-yellow.svg)](https://42.fr/)

A C implementation of the classic Dining Philosophers problem using pthreads, mutexes, and careful synchronization to prevent deadlocks and race conditions.

> **42 School Project** | **Concurrent Programming** | **Thread Synchronization**

## 🚀 Quick Start

```bash
# Clone and build
git clone <your-repo-url>
cd Philosophers
make

# Run the program
./philo 4 410 200 200
```

## 📋 Table of Contents

- [About](#about)
- [Problem Description](#problem-description)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Technical Details](#technical-details)
- [Testing](#testing)

## 🎯 About

This project implements the Dining Philosophers problem, a classic computer science problem that demonstrates the challenges of concurrent programming and resource sharing. The solution uses pthreads for multithreading and mutexes for synchronization to ensure thread-safe operations.

### 📊 Project Status

- ✅ **Core Implementation**: Complete
- ✅ **Thread Safety**: Implemented with mutexes
- ✅ **Deadlock Prevention**: Fork ordering strategy
- ✅ **Memory Management**: Leak-free
- ✅ **Error Handling**: Comprehensive input validation
- ✅ **Code Quality**: Norminette compliant
- ✅ **Documentation**: Complete with examples

## 🧠 Problem Description

The Dining Philosophers problem involves:
- **N philosophers** sitting around a circular table
- **N forks** placed between each pair of philosophers
- Each philosopher alternates between **thinking** and **eating**
- To eat, a philosopher needs **both adjacent forks**
- The challenge is to prevent **deadlocks** and **starvation**

## ✨ Features

- 🧵 **Multithreaded Implementation**: Uses pthreads for concurrent execution
- 🔒 **Thread Safety**: Mutex-based synchronization prevents race conditions
- ⚡ **Deadlock Prevention**: Careful fork ordering prevents circular waits
- 🎯 **Starvation Prevention**: Fair resource allocation
- 📊 **Real-time Monitoring**: Live status updates and death detection
- 🎨 **Colorful Output**: Colored terminal output for better visualization
- 🛡️ **Error Handling**: Comprehensive input validation and error management
- 📈 **Performance Optimized**: Efficient memory management and minimal overhead

## 📁 Project Structure

```
Philosophers/
├── srcs/
│   ├── main.c                    # Main program entry point
│   ├── philo.h                   # Header file with all declarations
│   ├── threads.c                 # Thread management functions
│   ├── philosopher/              # Philosopher-related functions
│   │   ├── philosopher_init.c    # Philosopher initialization
│   │   ├── philosopher_free.c    # Memory cleanup
│   │   └── philosopher_struct.c  # Philosopher structure handling
│   ├── routines/                 # Core philosopher routines
│   │   ├── philosopher_routine.c # Main philosopher behavior
│   │   ├── routine_helpers.c     # Helper functions
│   │   ├── fork_management.c     # Fork handling logic
│   │   └── routine_utils.c       # Routine utilities
│   ├── table/                    # Table management
│   │   └── table_struct_handler.c # Table structure operations
│   └── utils/                    # Utility functions
│       ├── input_utils.c         # Input validation
│       ├── memory_utils.c        # Memory management
│       ├── philosopher_checks.c  # Philosopher state checks
│       ├── print_utils.c         # Output formatting
│       └── general_utils.c       # General utilities
├── objects/                      # Compiled object files
├── makefile                      # Build configuration
├── demo.sh                       # Demo script
├── .gitignore                    # Git ignore rules
└── README.md                     # This file
```

## 🚀 Installation

### Prerequisites

- **GCC** compiler (C99 standard)
- **Make** build system
- **pthread** library (usually included with GCC)
- **Linux/macOS** environment (WSL2 compatible)

### Build Instructions

1. **Clone the repository:**
   ```bash
   git clone <your-repo-url>
   cd Philosophers
   ```

2. **Compile the project:**
   ```bash
   make
   ```

3. **Clean build files (optional):**
   ```bash
   make clean      # Remove object files
   make fclean     # Remove all build files
   ```

4. **Run norminette check:**
   ```bash
   make norm       # Check code style compliance
   ```

5. **Run the demo script:**
   ```bash
   ./demo.sh       # Interactive demonstration
   ```

## 💻 Usage

### Basic Syntax

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Parameter | Description | Example |
|-----------|-------------|---------|
| `number_of_philosophers` | Number of philosophers (and forks) | `5` |
| `time_to_die` | Time in ms before a philosopher dies | `800` |
| `time_to_eat` | Time in ms a philosopher takes to eat | `200` |
| `time_to_sleep` | Time in ms a philosopher sleeps | `200` |
| `number_of_times_each_philosopher_must_eat` | Optional: Stop when all philosophers eat this many times | `7` |

## 🎮 Examples

### Basic Example
```bash
# 4 philosophers, die after 410ms, eat for 200ms, sleep for 200ms
./philo 4 410 200 200
```

### With Meal Limit
```bash
# 5 philosophers, stop when each has eaten 7 times
./philo 5 800 200 200 7
```

### Single Philosopher
```bash
# Special case: philosopher dies immediately (can't eat with only one fork)
./philo 1 800 200 200
```

### Expected Output
```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
400 2 has taken a fork
400 2 is eating
...
```

## 🔧 Technical Details

### Synchronization Strategy

1. **Fork Ordering**: Philosophers always pick up the lower-numbered fork first to prevent deadlocks
2. **Mutex Protection**: Each fork and shared data structure is protected by mutexes
3. **Death Monitoring**: A separate monitoring thread checks for philosopher deaths
4. **Atomic Operations**: Critical sections are kept minimal to reduce contention

### Data Structures

- **`t_philo`**: Individual philosopher state and timing information
- **`t_table`**: Shared table state, forks, and synchronization primitives
- **Mutex Arrays**: One mutex per fork, plus print and death mutexes

### Memory Management

- **Dynamic Allocation**: All structures allocated at runtime
- **Proper Cleanup**: All resources freed on program exit
- **Error Handling**: Graceful failure with proper cleanup

## 🧪 Testing

### Test Cases

```bash
# Test basic functionality
./philo 4 410 200 200

# Test with meal limit
./philo 5 800 200 200 7

# Test single philosopher
./philo 1 800 200 200

# Test edge cases
./philo 0 800 200 200    # Should show error
./philo 200 800 200 200  # Large number test
```

### Performance Testing

```bash
# Time the execution
time ./philo 10 800 200 200 5

# Monitor resource usage
valgrind --tool=helgrind ./philo 4 410 200 200
```

## 🎨 Output Format

The program provides colored, timestamped output:

- **🟢 Green**: Normal operations (eating, sleeping, thinking)
- **🔴 Red**: Death events
- **🟡 Yellow**: Fork acquisition
- **🔵 Blue**: Status messages

## 🐛 Troubleshooting

### Common Issues

1. **Compilation Errors**: Ensure you have pthread support
   ```bash
   gcc -pthread -o philo *.c
   ```

2. **Segmentation Faults**: Check for proper memory allocation and cleanup

3. **Deadlocks**: The implementation prevents deadlocks through fork ordering

4. **Infinite Loops**: Check for proper exit conditions in philosopher routines

## 📊 Performance

- **Memory Usage**: O(n) where n is the number of philosophers
- **Time Complexity**: O(1) per philosopher operation
- **Scalability**: Tested up to 200 philosophers
- **Thread Overhead**: Minimal with efficient mutex usage


---

## 🏆 Achievements

- ✅ **Thread Safety**: No race conditions or data corruption
- ✅ **Deadlock Prevention**: Robust synchronization strategy
- ✅ **Memory Management**: Leak-free implementation
- ✅ **Error Handling**: Comprehensive input validation
- ✅ **Performance**: Optimized for large numbers of philosophers
- ✅ **Code Quality**: Clean, readable, and well-documented

---

*Made at Lisbon 42 School*