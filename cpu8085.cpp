#include "cpu8085.h"
#include <sstream>
#include <iomanip>
#include <cstring>

CPU8085::CPU8085() {
    reset();
}

void CPU8085::reset() {
    A = B = C = D = E = H = L = 0;
    SP = 0xFFFF;
    PC = 0x0000;
    flags = {false, false, false, false, false};
    memory.fill(0);
    halted = false;
    interruptEnabled = false;
}

uint8_t CPU8085::fetchByte() {
    return memory[PC++];
}

uint16_t CPU8085::fetchWord() {
    uint8_t low = fetchByte();
    uint8_t high = fetchByte();
    return (high << 8) | low;
}

void CPU8085::step() {
    if (halted) return;
    
    uint8_t opcode = fetchByte();
    executeInstruction(opcode);
}

void CPU8085::executeInstruction(uint8_t opcode) {
    // Implement basic 8085 instructions
    switch (opcode) {
        case 0x00: // NOP
            break;
            
        case 0x76: // HLT
            halted = true;
            break;
            
        // MOV instructions (examples)
        case 0x7F: A = A; break; // MOV A, A
        case 0x78: A = B; break; // MOV A, B
        case 0x79: A = C; break; // MOV A, C
        case 0x7A: A = D; break; // MOV A, D
        case 0x7B: A = E; break; // MOV A, E
        case 0x7C: A = H; break; // MOV A, H
        case 0x7D: A = L; break; // MOV A, L
        
        case 0x47: B = A; break; // MOV B, A
        case 0x4F: C = A; break; // MOV C, A
        case 0x57: D = A; break; // MOV D, A
        case 0x5F: E = A; break; // MOV E, A
        case 0x67: H = A; break; // MOV H, A
        case 0x6F: L = A; break; // MOV L, A
        
        // MVI (Move Immediate) instructions
        case 0x3E: A = fetchByte(); break; // MVI A, data
        case 0x06: B = fetchByte(); break; // MVI B, data
        case 0x0E: C = fetchByte(); break; // MVI C, data
        case 0x16: D = fetchByte(); break; // MVI D, data
        case 0x1E: E = fetchByte(); break; // MVI E, data
        case 0x26: H = fetchByte(); break; // MVI H, data
        case 0x2E: L = fetchByte(); break; // MVI L, data
        
        // ADD instructions
        case 0x87: A = add(A); break; // ADD A
        case 0x80: A = add(B); break; // ADD B
        case 0x81: A = add(C); break; // ADD C
        case 0x82: A = add(D); break; // ADD D
        case 0x83: A = add(E); break; // ADD E
        case 0x84: A = add(H); break; // ADD H
        case 0x85: A = add(L); break; // ADD L
        
        // SUB instructions
        case 0x97: A = sub(A); break; // SUB A
        case 0x90: A = sub(B); break; // SUB B
        case 0x91: A = sub(C); break; // SUB C
        case 0x92: A = sub(D); break; // SUB D
        case 0x93: A = sub(E); break; // SUB E
        case 0x94: A = sub(H); break; // SUB H
        case 0x95: A = sub(L); break; // SUB L
        
        // INR (Increment) instructions
        case 0x3C: A++; updateFlags(A); break; // INR A
        case 0x04: B++; updateFlags(B); break; // INR B
        case 0x0C: C++; updateFlags(C); break; // INR C
        case 0x14: D++; updateFlags(D); break; // INR D
        case 0x1C: E++; updateFlags(E); break; // INR E
        case 0x24: H++; updateFlags(H); break; // INR H
        case 0x2C: L++; updateFlags(L); break; // INR L
        
        // JMP instruction
        case 0xC3: PC = fetchWord(); break; // JMP addr
        
        default:
            // Unknown opcode - could log or handle error
            break;
    }
}

uint8_t CPU8085::add(uint8_t value, bool withCarry) {
    uint16_t result = A + value + (withCarry && flags.CY ? 1 : 0);
    flags.CY = (result > 0xFF);
    flags.AC = ((A & 0x0F) + (value & 0x0F) + (withCarry && flags.CY ? 1 : 0)) > 0x0F;
    updateFlags(result & 0xFF);
    return result & 0xFF;
}

uint8_t CPU8085::sub(uint8_t value, bool withBorrow) {
    uint16_t result = A - value - (withBorrow && flags.CY ? 1 : 0);
    flags.CY = (result > 0xFF);
    flags.AC = ((A & 0x0F) < ((value & 0x0F) + (withBorrow && flags.CY ? 1 : 0)));
    updateFlags(result & 0xFF);
    return result & 0xFF;
}

void CPU8085::updateFlags(uint8_t result) {
    flags.Z = (result == 0);
    flags.S = (result & 0x80) != 0;
    
    // Calculate parity
    int bits = 0;
    for (int i = 0; i < 8; i++) {
        if (result & (1 << i)) bits++;
    }
    flags.P = (bits % 2 == 0);
}

void CPU8085::push(uint16_t value) {
    memory[--SP] = (value >> 8) & 0xFF;
    memory[--SP] = value & 0xFF;
}

uint16_t CPU8085::pop() {
    uint8_t low = memory[SP++];
    uint8_t high = memory[SP++];
    return (high << 8) | low;
}

std::string CPU8085::getRegisterState() const {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    oss << "A:" << std::setw(2) << (int)A << " "
        << "B:" << std::setw(2) << (int)B << " "
        << "C:" << std::setw(2) << (int)C << " "
        << "D:" << std::setw(2) << (int)D << " "
        << "E:" << std::setw(2) << (int)E << " "
        << "H:" << std::setw(2) << (int)H << " "
        << "L:" << std::setw(2) << (int)L << "\n"
        << "SP:" << std::setw(4) << SP << " "
        << "PC:" << std::setw(4) << PC;
    return oss.str();
}

std::string CPU8085::getFlagsState() const {
    std::ostringstream oss;
    oss << "S:" << flags.S << " "
        << "Z:" << flags.Z << " "
        << "AC:" << flags.AC << " "
        << "P:" << flags.P << " "
        << "CY:" << flags.CY;
    return oss.str();
}

uint8_t CPU8085::getMemory(uint16_t address) const {
    return memory[address];
}

void CPU8085::setMemory(uint16_t address, uint8_t value) {
    memory[address] = value;
}

void CPU8085::loadProgram(const uint8_t* program, size_t size, uint16_t startAddress) {
    std::memcpy(&memory[startAddress], program, size);
    PC = startAddress;
}
