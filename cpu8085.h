#ifndef CPU8085_H
#define CPU8085_H

#include <cstdint>
#include <array>
#include <string>

class CPU8085 {
public:
    // Registers
    uint8_t A;      // Accumulator
    uint8_t B, C;   // BC register pair
    uint8_t D, E;   // DE register pair
    uint8_t H, L;   // HL register pair
    uint16_t SP;    // Stack Pointer
    uint16_t PC;    // Program Counter
    
    // Flags
    struct Flags {
        bool S;  // Sign
        bool Z;  // Zero
        bool AC; // Auxiliary Carry
        bool P;  // Parity
        bool CY; // Carry
    } flags;
    
    // Memory (64KB)
    std::array<uint8_t, 65536> memory;
    
    // State
    bool halted;
    bool interruptEnabled;
    
    CPU8085();
    void reset();
    void step();  // Execute one instruction
    uint8_t fetchByte();
    uint16_t fetchWord();
    
    // Helper functions
    std::string getRegisterState() const;
    std::string getFlagsState() const;
    uint8_t getMemory(uint16_t address) const;
    void setMemory(uint16_t address, uint8_t value);
    
    // Load program into memory
    void loadProgram(const uint8_t* program, size_t size, uint16_t startAddress = 0x0000);
    
private:
    void executeInstruction(uint8_t opcode);
    void updateFlags(uint8_t result);
    void updateFlagsLogical(uint8_t result);
    uint8_t add(uint8_t value, bool withCarry = false);
    uint8_t sub(uint8_t value, bool withBorrow = false);
    void push(uint16_t value);
    uint16_t pop();
};

#endif // CPU8085_H
