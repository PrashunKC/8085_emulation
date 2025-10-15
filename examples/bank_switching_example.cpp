/**
 * Bank Switching Example
 * 
 * This example demonstrates how to use bank switching for a simple
 * multi-tasking scenario where each task has its own memory bank.
 */

#include "../cpu8085.h"
#include <iostream>
#include <iomanip>

void printBankContents(CPU8085& cpu, int bank, uint16_t start, uint16_t len) {
    cpu.setBank(bank);
    std::cout << "Bank " << bank << " [0x" << std::hex << start << "]: ";
    for (uint16_t i = 0; i < len; i++) {
        std::cout << std::setw(2) << std::setfill('0') 
                  << (int)cpu.getMemory(start + i) << " ";
    }
    std::cout << std::dec << std::endl;
}

int main() {
    CPU8085 cpu;
    
    std::cout << "=== Bank Switching Example: Simple Task Manager ===" << std::endl;
    std::cout << std::endl;
    
    // Enable bank switching
    cpu.enableBankSwitching(true);
    std::cout << "Bank switching enabled (" << (int)cpu.getBankCount() 
              << " banks available)" << std::endl;
    std::cout << std::endl;
    
    // ===================================================================
    // Scenario: Simple task manager with 3 tasks
    // Each task gets its own memory bank for data storage
    // Task switching is done by changing the current bank
    // ===================================================================
    
    // Task 1: Counter task (stores count in bank 0)
    std::cout << "Task 1 (Bank 0): Counter" << std::endl;
    cpu.setBank(0);
    for (int i = 0; i < 10; i++) {
        cpu.setMemory(0x8000 + i, i * 10);  // Store: 0, 10, 20, 30...
    }
    std::cout << "  Stored values: 0, 10, 20, 30, ..., 90" << std::endl;
    printBankContents(cpu, 0, 0x8000, 10);
    std::cout << std::endl;
    
    // Task 2: Pattern generator (stores pattern in bank 1)
    std::cout << "Task 2 (Bank 1): Pattern Generator" << std::endl;
    cpu.setBank(1);
    for (int i = 0; i < 10; i++) {
        cpu.setMemory(0x8000 + i, 0xAA + (i % 2));  // Store: 0xAA, 0xAB, 0xAA, 0xAB...
    }
    std::cout << "  Stored pattern: 0xAA, 0xAB alternating" << std::endl;
    printBankContents(cpu, 1, 0x8000, 10);
    std::cout << std::endl;
    
    // Task 3: Fibonacci generator (stores sequence in bank 2)
    std::cout << "Task 3 (Bank 2): Fibonacci Sequence" << std::endl;
    cpu.setBank(2);
    uint8_t a = 0, b = 1;
    cpu.setMemory(0x8000, a);
    cpu.setMemory(0x8001, b);
    for (int i = 2; i < 10; i++) {
        uint8_t next = (a + b) & 0xFF;  // Keep in 8-bit range
        cpu.setMemory(0x8000 + i, next);
        a = b;
        b = next;
    }
    std::cout << "  Stored sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34" << std::endl;
    printBankContents(cpu, 2, 0x8000, 10);
    std::cout << std::endl;
    
    // ===================================================================
    // Simulate task switching with a simple scheduler
    // ===================================================================
    
    std::cout << "--- Simulating Task Scheduler ---" << std::endl;
    std::cout << std::endl;
    
    // Program that switches between tasks and reads their data
    uint8_t program[] = {
        // Read first value from Task 1 (Bank 0)
        0x3E, 0x00,        // MVI A, 0x00 - Select bank 0
        0xD3, 0xFF,        // OUT 0xFF - Switch to bank 0
        0x3A, 0x00, 0x80,  // LDA 0x8000 - Read first value
        0x47,              // MOV B, A - Store in B
        
        // Read first value from Task 2 (Bank 1)
        0x3E, 0x01,        // MVI A, 0x01 - Select bank 1
        0xD3, 0xFF,        // OUT 0xFF - Switch to bank 1
        0x3A, 0x00, 0x80,  // LDA 0x8000 - Read first value
        0x4F,              // MOV C, A - Store in C
        
        // Read first value from Task 3 (Bank 2)
        0x3E, 0x02,        // MVI A, 0x02 - Select bank 2
        0xD3, 0xFF,        // OUT 0xFF - Switch to bank 2
        0x3A, 0x00, 0x80,  // LDA 0x8000 - Read first value
        0x57,              // MOV D, A - Store in D
        
        // Sum all three values
        0x78,              // MOV A, B - Load task 1 value
        0x81,              // ADD C - Add task 2 value
        0x82,              // ADD D - Add task 3 value
        0x67,              // MOV H, A - Store sum in H
        
        0x76               // HLT
    };
    
    cpu.reset();
    cpu.enableBankSwitching(true);
    cpu.loadProgram(program, sizeof(program), 0x0000);
    
    // Restore task data (reset cleared it)
    cpu.setBank(0);
    for (int i = 0; i < 10; i++) cpu.setMemory(0x8000 + i, i * 10);
    cpu.setBank(1);
    for (int i = 0; i < 10; i++) cpu.setMemory(0x8000 + i, 0xAA + (i % 2));
    cpu.setBank(2);
    a = 0; b = 1;
    cpu.setMemory(0x8000, a);
    cpu.setMemory(0x8001, b);
    for (int i = 2; i < 10; i++) {
        uint8_t next = (a + b) & 0xFF;
        cpu.setMemory(0x8000 + i, next);
        a = b;
        b = next;
    }
    
    std::cout << "Executing scheduler program..." << std::endl;
    
    int steps = 0;
    while (!cpu.halted && steps < 100) {
        cpu.step();
        steps++;
    }
    
    std::cout << "Scheduler executed in " << steps << " steps" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Results:" << std::endl;
    std::cout << "  B (Task 1 first value): " << (int)cpu.B << std::endl;
    std::cout << "  C (Task 2 first value): 0x" << std::hex << (int)cpu.C << std::dec << std::endl;
    std::cout << "  D (Task 3 first value): " << (int)cpu.D << std::endl;
    std::cout << "  H (Sum of all): " << (int)cpu.H << " (0x" << std::hex << (int)cpu.H << ")" << std::dec << std::endl;
    std::cout << std::endl;
    
    // Verify result
    int expected = 0 + 0xAA + 0;  // Task 1: 0, Task 2: 0xAA, Task 3: 0
    if (cpu.H == expected) {
        std::cout << "✓ Scheduler correctly accessed all task memory banks!" << std::endl;
    } else {
        std::cout << "✗ Unexpected result (expected " << expected << ")" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "=== Example Complete ===" << std::endl;
    
    return (cpu.H == expected) ? 0 : 1;
}
