# Mini Project: Contacts Directory using Hash Tables and Linked Lists

This project implements a simple contacts directory using hash tables and linked lists. The code is thoroughly commented (in French) to aid understanding.

## Getting Started

### Prerequisites

To compile and run the code, make sure your system has `make` and a C compiler installed. You may also need `valgrind` to test for memory leaks.

### Compiling the Code

To compile the code, run:

```bash
$ make
```
### Running Tests
Navigate to the `tests` directory to run the available tests:
```bash
$ cd tests
$ ./directory-01-test # Run the first test as an example
```

Each test file evaluates different aspects of the contacts directory. Below is a description of each test:

- **directory-01-test**: Memory test (verifies if the `free_dir` function properly frees memory).
- **directory-02-test**: Tests if contact insertion in the hash table works.
- **directory-03-test**: Similar to `directory-02`, but with three contacts.
- **directory-04-test**: Tests if the `dir_lookup_num` function works as expected.
- **directory-05-test**: Tests the functionality of the `dir_delete` function.
- **directory-06-test**: Resizing test – adds a large number of contacts, causing the hash table to double in size.
- **directory-07-test**: Resizing test – deletes contacts, causing the hash table to shrink.

Feel free to add your tests or extend the functionality of the directory!

### Example

To run the first test:
```bash
$ ./directory-01-test
```
### Checking for Memory Leaks

To check for memory leaks using `valgrind`, you can run the following command:
```bash
$ valgrind ./directory-01-test # Example: running the memory test
```
