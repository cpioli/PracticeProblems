# PracticeProblems
C++ practice problems to test out data structures, learn new tools, and solve common problems

This is a large project where I kept several different practice problems, learning how to use and implement different resources provided by the C++ library.

<h2>nQueens</h2>

An optimized implementation of the nQueens algorithm. It uses 3 unsigned 64-bit integers to store the positions of queens on a chess board: one to house the position of all columns, and two to house the position of queens in diagonal directions.

Checking if a queen is already in a position is a simple procedure requiring minimal processes: simply XOR the queen's position into the respective unsigned int, and check if the previous integer value is less than the current integer value. If so, the queen fits. (this will not work with signed ints, because if the far left bit is turned on, that integer value is now negative).

On Leetcode, this algorithm beats 100% of all other implementations, in processing speed and memory usage.

<h2>Multithreaded nQueens</h2>

My optimized nQueens problem, implemented with threads to run concurrently. This is originally a test to make sure I understand how to properly pool threads, manage mutexes, and distribute resources. This modified algorithm divides the problem into n-subproblems, asking each thread to solve (n-1)Queens, where a queen occupies row 0 at column i. When a solution is found, the chessboard is outputted. Muteces are used to reserve cout so only one board is printed at a time. Otherwise, all threads get their own copy of the variables.

The original algorithm runs so fast that the multithreaded version of nQueens runs slower for all n <= 8! I believe this is because the I've optimized nQueens to be so fast that it runs in less time than it requires to initialize new threads (1500ms + 300ms for each additional thread)! When n > 9, however, multithreading improves speeds by up to 50%.

As you might have guessed, this problem is not perfectly optimized. In cases where the number of processors doesn't evenly divide into n (i.e. n % processors != 0), some threads need to run the remaining subproblems. This causes a delay in program termination, because the main thread has to wait for all subthreads to complete before they can join. If I found a way to more evenly distribute the work amongst all p processors, that would be the final optimization. That's definitely a task I should come back to in the future.

<h2>LinkedList</h2>

A complete implementation of a LinkedList template class, with some overloaded operators (==, !=, ++, and <<) and iterators.

<h2>Binary Tree</h2>

An implementation of a Binary Tree template class with three functions to output nodes: preorder, inorder, and postorder.

<h2>Practice Problems</h2>

A .cpp file containing the tests to run against nQueens, data structures, and the tasks listed below:

<h3>Simple Calculator</h3>

void runSimpleCalculator(string &_filename) opens a file and reads each line, which is composed of integers, the plus sign, and the minus sign.

int calc(string &_line) converts the string into mathematical operations and returns the numeric result.

<h3>Complex Calculator</h3>

complexNumber is a small struct designed to store a complex number's whole number and imaginary number.

void runComplexCalculator(string &_filename) reads lines from a file and runs them through the complex calculator.

complexNumber complexCalc(string &line) accepts a string and converts characters into complex numbers, then performs the correct calculations on them, returning the answer as a complex number.
