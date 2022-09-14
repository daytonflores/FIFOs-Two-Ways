# PES-Assignment-2
Code for Assign 2 for PRES, ECEN 5813-001B, Fall 2022
 
# Build and Run

## Unix
- Navigate to directory of Makefile
- Run "make"
- Run "./main"

## Windows
- Navigate to directory of Makefile
- Run "make"
- Run "./main.exe" in PowerShell or "main.exe" in Command Prompt

# Unit Tests

## LLFIFO

- In main.c, ensure the call to llfifo() is not commented out
- In test_llfifo.c, you may comment/uncomment the following as specific to which function(s) you wish to test:
	- #define TEST_LLFIFO_CREATE
	- #define TEST_LLFIFO_ENQUEUE
	- #define TEST_LLFIFO_DEQUEUE
	- #define TEST_LLFIFO_CAPACITY
	- #define TEST_LLFIFO_LENGTH
	- #define TEST_LLFIFO_DESTROY
- Test cases are hard-coded in the test functions themselves since these are state-dependent

## CBFIFO

- In main.c, ensure the call to cbfifo() is not commented out
- In test_cbfifo.c, you may comment/uncomment the following as specific to which function(s) you wish to test:
	- #define TEST_CBFIFO_ENQUEUE
	- #define TEST_CBFIFO_DEQUEUE
	- #define TEST_CBFIFO_CAPACITY
	- #define TEST_CBFIFO_LENGTH
- Test cases are hard-coded in the test functions themselves since these are state-dependent. As long as asserts check out we can consider these tests passed
	- Details after each transaction will be dumped to the terminal screen

