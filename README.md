# philosophers

[![42](https://img.shields.io/badge/42-Project-blue)](https://42.fr)
[![C](https://img.shields.io/badge/Language-C-green)](https://en.wikipedia.org/wiki/C_(programming_language))

> Simulate the Dining Philosophers problem using threads and mutexes.

## Overview

`philosophers` is a 42 School Rank 3 project. The goal is to solve the classic Dining Philosophers problem: N philosophers sit around a table with N forks, each needing two forks to eat. The implementation uses pthreads and mutexes to prevent deadlocks and race conditions.

## Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Parameter | Description |
|-----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Milliseconds before a philosopher starves |
| `time_to_eat` | Milliseconds a philosopher takes to eat |
| `time_to_sleep` | Milliseconds a philosopher sleeps |
| `number_of_times_each_philosopher_must_eat` | Optional: stop when all philosophers reach this count |

### Examples

```bash
./philo 4 410 200 200
./philo 5 800 200 200 7
./philo 1 800 200 200   # dies immediately — only one fork available
```

### Output format

```
timestamp_in_ms philosopher_number action
```

Actions: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`

## How it works

- Each fork is protected by a mutex
- A monitoring thread checks for philosopher deaths without blocking eating
- Fork pickup order (lower-numbered first) prevents circular waits and deadlocks

## Project structure

```
philosophers/
├── srcs/
│   ├── main.c
│   ├── philo.h
│   ├── threads.c
│   ├── philosopher/     # Init, free, struct handling
│   ├── routines/        # Eat/sleep/think loop, fork management
│   ├── table/           # Shared table state
│   └── utils/           # Input validation, printing, memory
└── makefile
```

## Make targets

| Target | Description |
|--------|-------------|
| `make` | Build the binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Rebuild from scratch |
| `make norm` | Run norminette |

## Author

**Laher Maciel**
- GitHub: [@LaherMaciel](https://github.com/LaherMaciel)
- 42 Login: lawences
