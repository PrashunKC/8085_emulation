# Bank Switching Examples

This directory contains example programs demonstrating the use of bank switching in the 8085 emulator.

## Building Examples

All examples can be compiled using g++:

```bash
cd ..
g++ -std=c++17 -o examples/bank_switching_example examples/bank_switching_example.cpp cpu8085.cpp
```

## Running Examples

After building, run the example:

```bash
./examples/bank_switching_example
```

## Available Examples

### bank_switching_example.cpp

A practical demonstration of bank switching for a simple task manager scenario.

**Features demonstrated:**
- Enabling bank switching
- Assigning memory banks to different tasks
- Switching between banks using assembly code (OUT/IN instructions)
- Accessing task-specific data from different banks
- Simulating a simple task scheduler

**Scenario:**
The example creates three tasks:
1. **Task 1 (Bank 0)**: Counter - stores incremental values
2. **Task 2 (Bank 1)**: Pattern Generator - stores alternating pattern
3. **Task 3 (Bank 2)**: Fibonacci Sequence - stores Fibonacci numbers

A scheduler program then switches between banks to read data from each task and compute a sum.

**Expected Output:**
```
=== Bank Switching Example: Simple Task Manager ===

Bank switching enabled (8 banks available)

Task 1 (Bank 0): Counter
  Stored values: 0, 10, 20, 30, ..., 90
  ...

✓ Scheduler correctly accessed all task memory banks!
```

## Creating Your Own Examples

To create a new example:

1. Create a new `.cpp` file in this directory
2. Include the CPU header: `#include "../cpu8085.h"`
3. Enable bank switching: `cpu.enableBankSwitching(true);`
4. Use `cpu.setBank(n)` to switch banks programmatically
5. Use OUT 0xFF in assembly to switch banks from code
6. Compile with: `g++ -std=c++17 -o your_example your_example.cpp ../cpu8085.cpp`

## See Also

- [../BANK_SWITCHING.md](../BANK_SWITCHING.md) - Comprehensive bank switching guide
- [../README.md](../README.md) - Main emulator documentation
- [../bank_switching_test.cpp](../bank_switching_test.cpp) - Test suite with more examples
