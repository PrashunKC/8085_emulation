// Bank Switching Test Program
// Demonstrates the bank switching functionality of the 8085 emulator

#include "cpu8085.h"
#include <iostream>
#include <iomanip>

void printMemoryContents(CPU8085& cpu, uint16_t address, int count) {
    std::cout << "Memory at 0x" << std::hex << std::setw(4) << std::setfill('0') 
              << address << ": ";
    for (int i = 0; i < count; i++) {
        std::cout << std::setw(2) << (int)cpu.getMemory(address + i) << " ";
    }
    std::cout << std::dec << std::endl;
}

int main() {
    CPU8085 cpu;
    
    std::cout << "=== 8085 Bank Switching Test ===" << std::endl << std::endl;
    
    // Test 1: Basic bank switching
    std::cout << "Test 1: Basic Bank Switching (Banked Memory 0x8000+)" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    
    cpu.enableBankSwitching(true);
    std::cout << "Bank switching enabled" << std::endl;
    std::cout << "Current bank: " << (int)cpu.getBank() << std::endl << std::endl;
    
    // Write different data to the same address in different banks
    // Use 0x8000+ for banked memory area
    std::cout << "Writing unique values to address 0x8000 in each bank..." << std::endl;
    for (int bank = 0; bank < cpu.getBankCount(); bank++) {
        cpu.setBank(bank);
        cpu.setMemory(0x8000, 0x10 + bank);  // Bank 0: 0x10, Bank 1: 0x11, etc.
        std::cout << "  Bank " << bank << ": wrote 0x" 
                  << std::hex << (0x10 + bank) << std::dec << std::endl;
    }
    std::cout << std::endl;
    
    // Read back from each bank
    std::cout << "Reading back from address 0x8000 in each bank..." << std::endl;
    bool test1_passed = true;
    for (int bank = 0; bank < cpu.getBankCount(); bank++) {
        cpu.setBank(bank);
        uint8_t value = cpu.getMemory(0x8000);
        bool correct = (value == 0x10 + bank);
        std::cout << "  Bank " << bank << ": read 0x" 
                  << std::hex << (int)value << std::dec 
                  << (correct ? " ✓" : " ✗") << std::endl;
        if (!correct) test1_passed = false;
    }
    std::cout << "Test 1: " << (test1_passed ? "PASSED" : "FAILED") << std::endl << std::endl;
    
    // Test 2: Bank switching via I/O instructions
    std::cout << "Test 2: Bank Switching via I/O Instructions" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    
    // Program to switch banks using OUT instruction
    // Use 0x8000+ addresses for banked memory
    uint8_t program[] = {
        // Write to bank 0
        0x3E, 0x00,        // MVI A, 0x00 - Select bank 0
        0xD3, 0xFF,        // OUT 0xFF - Switch to bank 0
        0x3E, 0xAA,        // MVI A, 0xAA - Load value to write
        0x32, 0x00, 0x80,  // STA 0x8000 - Store to banked memory
        
        // Write to bank 1
        0x3E, 0x01,        // MVI A, 0x01 - Select bank 1
        0xD3, 0xFF,        // OUT 0xFF - Switch to bank 1
        0x3E, 0xBB,        // MVI A, 0xBB - Load different value
        0x32, 0x00, 0x80,  // STA 0x8000 - Store to same address
        
        // Read back from bank 0
        0x3E, 0x00,        // MVI A, 0x00 - Select bank 0
        0xD3, 0xFF,        // OUT 0xFF - Switch to bank 0
        0x3A, 0x00, 0x80,  // LDA 0x8000 - Load from memory
        0x47,              // MOV B, A - Save in B register
        
        // Read back from bank 1
        0x3E, 0x01,        // MVI A, 0x01 - Select bank 1
        0xD3, 0xFF,        // OUT 0xFF - Switch to bank 1
        0x3A, 0x00, 0x80,  // LDA 0x8000 - Load from memory
        0x4F,              // MOV C, A - Save in C register
        
        // Read current bank into A
        0xDB, 0xFF,        // IN 0xFF - Read current bank
        
        0x76               // HLT
    };
    
    cpu.reset();
    cpu.enableBankSwitching(true);
    cpu.loadProgram(program, sizeof(program), 0x0000);
    
    std::cout << "Running program that uses OUT/IN to switch banks..." << std::endl;
    
    // Execute the program
    int steps = 0;
    while (!cpu.halted && steps < 100) {
        cpu.step();
        steps++;
    }
    
    std::cout << "Program executed in " << steps << " steps" << std::endl;
    std::cout << "Register B (from bank 0): 0x" << std::hex << (int)cpu.B << std::dec << std::endl;
    std::cout << "Register C (from bank 1): 0x" << std::hex << (int)cpu.C << std::dec << std::endl;
    std::cout << "Register A (current bank): " << (int)cpu.A << std::endl;
    
    bool test2_passed = (cpu.B == 0xAA && cpu.C == 0xBB && cpu.A == 1);
    std::cout << "Test 2: " << (test2_passed ? "PASSED" : "FAILED") << std::endl << std::endl;
    
    // Test 3: Memory isolation between banks
    std::cout << "Test 3: Memory Isolation Between Banks" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    
    cpu.reset();
    cpu.enableBankSwitching(true);
    
    // Fill bank 0 with pattern 0xAA in banked area (0x8000+)
    cpu.setBank(0);
    for (uint16_t addr = 0x8000; addr < 0x8100; addr++) {
        cpu.setMemory(addr, 0xAA);
    }
    
    // Fill bank 1 with pattern 0x55 in banked area
    cpu.setBank(1);
    for (uint16_t addr = 0x8000; addr < 0x8100; addr++) {
        cpu.setMemory(addr, 0x55);
    }
    
    // Verify bank 0 still has 0xAA
    cpu.setBank(0);
    bool bank0_ok = true;
    for (uint16_t addr = 0x8000; addr < 0x8100; addr++) {
        if (cpu.getMemory(addr) != 0xAA) {
            bank0_ok = false;
            break;
        }
    }
    
    // Verify bank 1 still has 0x55
    cpu.setBank(1);
    bool bank1_ok = true;
    for (uint16_t addr = 0x8000; addr < 0x8100; addr++) {
        if (cpu.getMemory(addr) != 0x55) {
            bank1_ok = false;
            break;
        }
    }
    
    std::cout << "Bank 0 isolation: " << (bank0_ok ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Bank 1 isolation: " << (bank1_ok ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3: " << (bank0_ok && bank1_ok ? "PASSED" : "FAILED") << std::endl << std::endl;
    
    // Summary
    std::cout << "=== Test Summary ===" << std::endl;
    std::cout << "Test 1 (Basic switching): " << (test1_passed ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (I/O instructions): " << (test2_passed ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (Memory isolation): " << (bank0_ok && bank1_ok ? "PASSED" : "FAILED") << std::endl;
    
    if (test1_passed && test2_passed && bank0_ok && bank1_ok) {
        std::cout << "\nAll tests PASSED! ✓" << std::endl;
        return 0;
    } else {
        std::cout << "\nSome tests FAILED! ✗" << std::endl;
        return 1;
    }
}
