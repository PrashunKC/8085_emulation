# 8085 Microprocessor Emulator

A graphical emulator for the Intel 8085 microprocessor written in C++ with Qt5.

## Features

- **Register Display**: Shows all 8085 registers (A, B, C, D, E, H, L, SP, PC)
- **Flags Display**: Shows processor flags (S, Z, AC, P, CY)
- **Memory Viewer**: Displays first 256 bytes of memory in hex format
- **Control Buttons**:
  - Reset: Reset CPU to initial state
  - Step: Execute one instruction
  - Run: Execute continuously
  - Stop: Stop continuous execution
  - Load Program: Load a sample program

## Implemented Instructions

**✅ 100% COMPLETE - ALL 256 OPCODES COVERED!**
- **246 valid instructions** fully implemented
- **10 undefined opcodes** handled (treated as NOP)

### Instruction Groups:
- **Data Transfer (64)**: MOV, MVI, LXI, LDA, STA, LHLD, SHLD, LDAX, STAX, XCHG
- **Arithmetic (68)**: ADD, ADI, ADC, ACI, SUB, SUI, SBB, SBI, INR, DCR, INX, DCX, DAD, DAA
- **Logical (40)**: ANA, ANI, XRA, XRI, ORA, ORI, CMP, CPI, RLC, RRC, RAL, RAR, CMA, CMC, STC
- **Branch (46)**: JMP, JNZ, JZ, JNC, JC, JPO, JPE, JP, JM, CALL, RET (with conditions), RST, PCHL
- **Stack (10)**: PUSH, POP, XTHL, SPHL
- **I/O & Control (18)**: IN, OUT, EI, DI, RIM, SIM, NOP, HLT

See [INSTRUCTIONS.md](INSTRUCTIONS.md) for complete instruction reference and [COMPLETE.md](COMPLETE.md) for detailed coverage analysis.

## Building

### Using Make:
```bash
make
./8085_emulator
```

### Using CMake:
```bash
mkdir build
cd build
cmake ..
make
./8085_emulator
```

## Usage

1. Click "Load Program" to load a sample program (adds 5 + 3)
2. Click "Step" to execute one instruction at a time
3. Or click "Run" to execute continuously
4. Watch the registers, flags, and memory update in real-time
5. The current PC location is highlighted in yellow in the memory view

## Extending

To add more instructions:
- Edit `cpu8085.cpp` and add cases in the `executeInstruction()` function
- Refer to 8085 instruction set documentation
- Opcodes are organized by category (MOV, MVI, ADD, etc.)

## Sample Program

The default loaded program demonstrates:
```asm
MVI A, 05h   ; Load 5 into accumulator
MVI B, 03h   ; Load 3 into B register
ADD B        ; Add B to A (result: A = 8)
HLT          ; Halt execution
```

## License

Free to use and modify.
