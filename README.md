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

Currently implemented basic instructions:
- NOP (0x00)
- HLT (0x76)
- MOV r1, r2 (various)
- MVI r, data (Move Immediate)
- ADD r (Add register to A)
- SUB r (Subtract register from A)
- INR r (Increment register)
- JMP addr (Jump to address)

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

This software is proprietary and confidential. All rights reserved.

Copyright (c) 2025, Prashun K.C.

Unauthorized copying, distribution, or modification of this software is 
strictly prohibited without express written permission from the copyright holder.

See the [LICENSE](LICENSE) file for more details.
