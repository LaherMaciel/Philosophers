#!/usr/bin/env python3

import subprocess
import sys
import os
import argparse
from datetime import datetime
import time

class Colors:
	RESET = '\033[0m'
	BOLD = '\033[1m'
	RED = '\033[0;31m'
	GREEN = '\033[0;32m'
	YELLOW = '\033[0;33m'
	BLUE = '\033[0;34m'
	PURPLE = '\033[0;35m'
	CYAN = '\033[0;36m'
	WHITE = '\033[0;37m'
	ERROR_BOLD = '\033[1;31m'
	OK_BOLD = '\033[1;32m'
	WARN_BOLD = '\033[1;33m'
	PURPLE_BOLD = '\033[1;35m'

class PhiloTester:
	def __init__(self, philo_path="./philo", iterations=10, times_to_eat=10):
		self.philo_path = philo_path
		self.iterations = iterations
		self.times_to_eat = times_to_eat
		self.count_correct_all = 0
		self.count_false_all = 0
		self.fails_dir = "fails/"
		
		# Create fails directory if it doesn't exist, or clean it if it does
		if not os.path.exists(self.fails_dir):
			os.makedirs(self.fails_dir)
		else:
			# Delete all existing log files in the fails directory
			for filename in os.listdir(self.fails_dir):
				if filename.endswith('.log'):
					os.remove(os.path.join(self.fails_dir, filename))
	
	def cleanup(self):
		"""Clean up fails directory if empty"""
		try:
			if os.path.exists(self.fails_dir):
				# Check if directory is empty or only contains .log files
				files = os.listdir(self.fails_dir)
				if not files:
					os.rmdir(self.fails_dir)
				elif len(files) > 0:
					log_files = [f for f in files if f.endswith('.log')]
					print(f"{Colors.CYAN}Failed test logs saved in {self.fails_dir} ({len(log_files)} files){Colors.RESET}")
		except:
			pass
	
	def run_philo_test(self, args, timeout=10):
		"""Run a single philosopher test with timeout"""
		try:
			cmd = [self.philo_path] + [str(arg) for arg in args]
			result = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
			return result.stdout.strip()
		except subprocess.TimeoutExpired:
			return "TIMEOUT"
		except Exception as e:
			return f"ERROR: {str(e)}"
	
	def print_loading_bar(self, current, total, passed, failed):
		"""Print an improved loading bar with test progress"""
		bar_length = 30
		progress = (current / total) * 100
		filled_length = int(bar_length * current // total)
		bar = '█' * filled_length + '░' * (bar_length - filled_length)
		print(f"\rProgress [{bar}] {current}/{total} ({progress:.1f}%) | ✓ {passed} ✗ {failed}", end='', flush=True)
	
	def test_case(self, test_args, should_die=True, test_name=""):
		"""Run a test case multiple times"""
		count_correct = 0
		count_false = 0
		
		print(f"\n\t{Colors.YELLOW}{' '.join(map(str, test_args))}{Colors.RESET}")
		if test_name:
			print(f"\t{Colors.CYAN}{test_name}{Colors.RESET}")
		
		for i in range(1, self.iterations + 1):
			self.print_loading_bar(i, self.iterations, count_correct, count_false)
			
			output = self.run_philo_test(test_args)
			
			# Check if philosopher died
			died = "died" in output.lower()
			
			if should_die:
				# Test expects death
				if died:
					count_correct += 1
					self.count_correct_all += 1
				else:
					# Save failed test to .log file
					log_filename = f"{self.fails_dir}{'-'.join(map(str, test_args))}_{i}.log"
					with open(log_filename, 'w') as f:
						f.write(f"Test case: {' '.join(map(str, test_args))}\n")
						f.write(f"Expected: Death\n")
						f.write(f"Actual: No death\n")
						f.write(f"Iteration: {i}\n")
						f.write(f"Timestamp: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
						f.write("-" * 50 + "\n")
						f.write("OUTPUT:\n")
						f.write(output if output else "No output")
					count_false += 1
					self.count_false_all += 1
			else:
				# Test expects no death
				if not died and output != "TIMEOUT":
					count_correct += 1
					self.count_correct_all += 1
				else:
					# Save failed test to .log file
					log_filename = f"{self.fails_dir}{'-'.join(map(str, test_args))}_{i}.log"
					with open(log_filename, 'w') as f:
						f.write(f"Test case: {' '.join(map(str, test_args))}\n")
						f.write(f"Expected: No death\n")
						f.write(f"Actual: {'Death' if died else 'Timeout'}\n")
						f.write(f"Iteration: {i}\n")
						f.write(f"Timestamp: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
						f.write("-" * 50 + "\n")
						f.write("OUTPUT:\n")
						f.write(output if output else "No output")
					count_false += 1
					self.count_false_all += 1
		
		# Clear the progress bar line and print final result
		print(f"\r{' ' * 80}", end='')  # Clear the line
		
		# Print test summary
		percent = (count_correct / self.iterations) * 100
		result_line = f"\r\t✓ {count_correct}/{self.iterations} passed ({percent:.0f}%)"
		
		if percent == 100:
			print(f"{result_line} {Colors.OK_BOLD}[PASS]{Colors.RESET}")
		else:
			print(f"{result_line} {Colors.ERROR_BOLD}[FAIL]{Colors.RESET}")
		
		if count_false > 0:
			print(f"\t{Colors.RED}✗ {count_false} failures saved to {self.fails_dir}*.log{Colors.RESET}")
		
		print("____________________________________________")
	
	def mandatory_tests(self):
		"""Run mandatory tests from eval sheet"""
		print(f"{Colors.CYAN}Mandatory tests{Colors.RESET}\n")
		self.test_case([1, 800, 200, 200, self.times_to_eat], should_die=True)
		self.test_case([5, 800, 200, 200, 7], should_die=False)
		self.test_case([4, 410, 200, 200, self.times_to_eat], should_die=False)
		self.test_case([4, 310, 200, 100, self.times_to_eat], should_die=True)
	
	def uneven_live_tests(self):
		"""Test uneven numbers - they shouldn't die"""
		print(f"{Colors.CYAN}Testing uneven numbers - they shouldn't die{Colors.RESET}\n")
		self.test_case([5, 800, 200, 200, self.times_to_eat], should_die=False)
		self.test_case([5, 610, 200, 200, self.times_to_eat], should_die=False)
		self.test_case([199, 610, 200, 200, self.times_to_eat], should_die=False)
	
	def uneven_live_extended_tests(self):
		"""Test uneven numbers (overkill) - they shouldn't die"""
		print(f"{Colors.CYAN}Testing uneven numbers (overkill) - they shouldn't die{Colors.RESET}\n")
		tests = [
			[5, 610, 200, 100, self.times_to_eat],
			[5, 601, 200, 200, self.times_to_eat],
			[31, 610, 200, 100, self.times_to_eat],
			[31, 610, 200, 200, self.times_to_eat],
			[31, 605, 200, 200, self.times_to_eat],
			[31, 601, 200, 200, self.times_to_eat],
			[131, 610, 200, 100, self.times_to_eat],
			[131, 610, 200, 200, self.times_to_eat],
			[131, 605, 200, 200, self.times_to_eat],
			[131, 601, 200, 200, self.times_to_eat],
			[199, 610, 200, 100, self.times_to_eat],
			[199, 610, 200, 200, self.times_to_eat],
			[199, 605, 200, 200, self.times_to_eat],
			[199, 601, 200, 200, self.times_to_eat]
		]
		for test in tests:
			self.test_case(test, should_die=False)
	
	def even_live_tests(self):
		"""Test even numbers - they shouldn't die"""
		print(f"{Colors.CYAN}Testing even numbers - they shouldn't die{Colors.RESET}")
		self.test_case([4, 410, 200, 100, self.times_to_eat], should_die=False)
		self.test_case([4, 410, 200, 200, self.times_to_eat], should_die=False)
		self.test_case([198, 610, 200, 200, self.times_to_eat], should_die=False)
		self.test_case([198, 800, 200, 200, self.times_to_eat], should_die=False)
	
	def even_live_extended_tests(self):
		"""Test even numbers (overkill) - they shouldn't die"""
		print(f"{Colors.CYAN}Testing even numbers (overkill) - they shouldn't die{Colors.RESET}")
		tests = [
			[50, 410, 200, 100, self.times_to_eat],
			[50, 410, 200, 200, self.times_to_eat],
			[50, 405, 200, 200, self.times_to_eat],
			[50, 401, 200, 200, self.times_to_eat],
			[130, 410, 200, 100, self.times_to_eat],
			[130, 410, 200, 200, self.times_to_eat],
			[130, 405, 200, 200, self.times_to_eat],
			[130, 401, 200, 200, self.times_to_eat],
			[198, 410, 200, 100, self.times_to_eat],
			[198, 410, 200, 200, self.times_to_eat],
			[198, 405, 200, 200, self.times_to_eat],
			[198, 401, 200, 200, self.times_to_eat]
		]
		for test in tests:
			self.test_case(test, should_die=False)
	
	def even_die_tests(self):
		"""Test even numbers - one should die"""
		print(f"{Colors.CYAN}Testing even numbers - one should die{Colors.RESET}")
		self.test_case([3, 599, 200, 200, self.times_to_eat], should_die=True)
		self.test_case([31, 599, 200, 200, self.times_to_eat], should_die=True)
		self.test_case([131, 596, 200, 200, self.times_to_eat], should_die=True)
	
	def even_die_extended_tests(self):
		"""Test even numbers - one should die"""
		print(f"{Colors.CYAN}Testing even numbers - one should die{Colors.RESET}")
		tests = [
			[4, 310, 200, 100, self.times_to_eat],
			[50, 396, 200, 200, self.times_to_eat],
			[50, 399, 200, 200, self.times_to_eat],
			[50, 400, 200, 200, self.times_to_eat],
			[130, 396, 200, 200, self.times_to_eat],
			[130, 399, 200, 200, self.times_to_eat],
			[130, 400, 200, 200, self.times_to_eat],
			[198, 396, 200, 200, self.times_to_eat],
			[198, 399, 200, 200, self.times_to_eat],
			[198, 400, 200, 200, self.times_to_eat]
		]
		for test in tests:
			self.test_case(test, should_die=True)
	
	def uneven_die_tests(self):
		"""Test uneven numbers - one should die"""
		print(f"{Colors.CYAN}Testing uneven numbers - one should die{Colors.RESET}")
		self.test_case([4, 310, 200, 100, self.times_to_eat], should_die=True)
		self.test_case([1, 800, 200, 100, self.times_to_eat], should_die=True)
	
	def uneven_die_extended_tests(self):
		"""Test uneven numbers - one should die"""
		print(f"{Colors.CYAN}Testing uneven numbers - one should die{Colors.RESET}")
		tests = [
			[3, 596, 200, 200, self.times_to_eat],
			[3, 599, 200, 200, self.times_to_eat],
			[3, 600, 200, 200, self.times_to_eat],
			[31, 596, 200, 200, self.times_to_eat],
			[31, 599, 200, 200, self.times_to_eat],
			[31, 600, 200, 200, self.times_to_eat],
			[131, 596, 200, 200, self.times_to_eat],
			[131, 599, 200, 200, self.times_to_eat],
			[131, 600, 200, 200, self.times_to_eat],
			[199, 596, 200, 200, self.times_to_eat],
			[199, 599, 200, 200, self.times_to_eat],
			[199, 600, 200, 200, self.times_to_eat]
		]
		for test in tests:
			self.test_case(test, should_die=True)
	
	def run_single_test(self, args):
		"""Run a single test case 20 times and return death count"""
		death_count = 0
		print(f"Testing: {' '.join(map(str, args))} (20 iterations)")
		
		for i in range(20):
			self.print_loading_bar(i + 1, 20, 20 - death_count, death_count)
			output = self.run_philo_test(args)
			if "died" in output.lower():
				death_count += 1
				# Save death case to log file
				log_filename = f"{self.fails_dir}single-test-{'-'.join(map(str, args))}_{i+1}.log"
				with open(log_filename, 'w') as f:
					f.write(f"Single test case: {' '.join(map(str, args))}\n")
					f.write(f"Death occurred\n")
					f.write(f"Iteration: {i+1}/20\n")
					f.write(f"Timestamp: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
					f.write("-" * 50 + "\n")
					f.write("OUTPUT:\n")
					f.write(output if output else "No output")
		
		print(f"\n\nResult: {death_count}/20 tests resulted in death")
		if death_count > 0:
			print(f"{Colors.YELLOW}Death cases saved to {self.fails_dir}single-test-*.log{Colors.RESET}")
		return death_count
	
	def print_final_results(self):
		"""Print final test results"""
		total_tests = self.count_correct_all + self.count_false_all
		if total_tests > 0:
			percent = (self.count_correct_all / total_tests) * 100
			print(f"\n{Colors.BOLD}RESULT: passed: {self.count_correct_all}\tfailed: {self.count_false_all}{Colors.RESET}")
			if percent == 100:
				print(f"\t{Colors.OK_BOLD}{percent:.0f}% - ALL TESTS PASSED!{Colors.RESET}")
			else:
				print(f"\t{Colors.ERROR_BOLD}{percent:.0f}% - SOME TESTS FAILED{Colors.RESET}")
		
		self.cleanup()

def main():
	parser = argparse.ArgumentParser(description='42 Philosophers Tester')
	parser.add_argument('-i', '--iterations', type=int, default=10, help='Number of iterations per test')
	parser.add_argument('-t', '--times-to-eat', type=int, default=10, help='Number of times each philosopher must eat')
	parser.add_argument('-p', '--philo-path', default='./philo', help='Path to philosopher executable')
	parser.add_argument('--test', choices=['mandatory', 'uneven-live', 'even-live', 'uneven-die', 'even-die', 'all', 'hardcore'], 
					   default='all', help='Which test suite to run')
	parser.add_argument('--single', nargs='+', type=int, help='Run a single test case (e.g., --single 5 800 200 200 7)')
	
	args = parser.parse_args()
	
	# Check if philo executable exists
	if not os.path.exists(args.philo_path):
		print(f"{Colors.RED}Error: Philosopher executable not found at {args.philo_path}{Colors.RESET}")
		print("Building philo...")
		try:
			subprocess.run(['make'], check=True)
		except subprocess.CalledProcessError:
			print(f"{Colors.RED}Failed to build philo{Colors.RESET}")
			sys.exit(1)
	
	tester = PhiloTester(args.philo_path, args.iterations, args.times_to_eat)
	
	print(f"\n{Colors.BLUE}42 Philosophers Tester{Colors.RESET}\t{datetime.now().strftime('%Y/%m/%d')}")
	print(f"Iterations: {args.iterations}\n")
	
	if args.single:
		if len(args.single) < 4 or len(args.single) > 5:
			print(f"{Colors.RED}Error: Single test requires 4 or 5 arguments (philos, die, eat, sleep, [meals]){Colors.RESET}")
			sys.exit(1)
		death_count = tester.run_single_test(args.single)
		sys.exit(0)
	
	if args.test == 'mandatory':
		tester.mandatory_tests()
	elif args.test == 'uneven-live':
		tester.uneven_live_tests()
	elif args.test == 'even-live':
		tester.even_live_tests()
	elif args.test == 'uneven-die':
		tester.uneven_die_tests()
	elif args.test == 'even-die':
		tester.even_die_tests()
	elif args.test == 'all':
		tester.mandatory_tests()
		tester.uneven_live_tests()
		tester.even_live_tests()
		tester.uneven_die_tests()
		tester.even_die_tests()
	elif args.test == 'hardcore':
		tester.mandatory_tests()
		tester.uneven_live_tests()
		tester.uneven_live_extended_tests()
		tester.even_live_tests()
		tester.even_live_extended_tests()
		tester.uneven_die_tests()
		tester.uneven_die_extended_tests()
		tester.even_die_tests()
		tester.even_die_extended_tests()
	
	tester.print_final_results()

if __name__ == "__main__":
	main()

