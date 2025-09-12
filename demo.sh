#!/bin/bash

# Philosophers Demo Script
# This script demonstrates the Dining Philosophers program with various test cases

echo "🍽️  Philosophers - Dining Philosophers Problem Demo"
echo "=================================================="
echo

# Check if the program exists
if [ ! -f "./philo" ]; then
    echo "❌ Error: philo executable not found. Please run 'make' first."
    exit 1
fi

echo "📋 Running test cases..."
echo

# Test 1: Basic functionality
echo "🧪 Test 1: Basic functionality (4 philosophers, 410ms to die)"
echo "Command: ./philo 4 410 200 200"
echo "Expected: Philosophers should eat, sleep, and think without dying"
echo "---"
timeout 5s ./philo 4 410 200 200
echo "---"
echo

# Test 2: Single philosopher
echo "🧪 Test 2: Single philosopher (should die immediately)"
echo "Command: ./philo 1 800 200 200"
echo "Expected: Philosopher should die after 800ms"
echo "---"
./philo 1 800 200 200
echo "---"
echo

# Test 3: With meal limit
echo "🧪 Test 3: With meal limit (5 philosophers, stop after 3 meals each)"
echo "Command: ./philo 5 800 200 200 3"
echo "Expected: Program should stop when all philosophers have eaten 3 times"
echo "---"
timeout 10s ./philo 5 800 200 200 3
echo "---"
echo

# Test 4: Error handling
echo "🧪 Test 4: Error handling (invalid input)"
echo "Command: ./philo 0 800 200 200"
echo "Expected: Should show error message"
echo "---"
./philo 0 800 200 200
echo "---"
echo

# Test 5: Large number of philosophers
echo "🧪 Test 5: Large number of philosophers (10 philosophers)"
echo "Command: ./philo 10 800 200 200"
echo "Expected: Should handle 10 philosophers without issues"
echo "---"
timeout 8s ./philo 10 800 200 200
echo "---"
echo

echo "✅ Demo completed!"
echo
echo "💡 Tips:"
echo "   - Use Ctrl+C to stop long-running tests"
echo "   - Adjust time values to see different behaviors"
echo "   - Check for memory leaks with: valgrind --leak-check=full ./philo 4 410 200 200"
echo "   - Check thread safety with: valgrind --tool=helgrind ./philo 4 410 200 200"
