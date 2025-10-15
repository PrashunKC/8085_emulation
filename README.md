# 8085 Microprocessor Emulator

A graphical emulator for the Intel 8085 microprocessor written in C++ with Qt5.

## Features

- **Register Display**: Shows all 8085 registers (A, B, C, D, E, H, L, SP, PC)
- **Flags Display**: Shows processor flags (S, Z, AC, P, CY)
- **Program Output Display**: Shows key register values in multiple formats (binary, hex, decimal) and program status
- **Memory Viewer**: Displays first 256 bytes of memory in hex format
- **Bank Switching**: Support for up to 8 memory banks (512KB total addressable memory)
  - Switch banks using OUT port 0xFF
  - Read current bank using IN port 0xFF
  - Each bank provides full 64KB address space
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

## Bank Switching

The emulator supports bank switching to extend memory beyond the 8085's native 64KB address space. This is useful for BIOS and OS development.

### Using Bank Switching

1. **Enable bank switching** programmatically:
```cpp
cpu.enableBankSwitching(true);
```

2. **Switch banks** from assembly code:
```asm
MVI A, 02h      ; Load bank number (0-7) into accumulator
OUT 0FFh        ; Switch to bank 2
; Access memory in 0x8000-0xFFFF range - now using bank 2
LXI H, 8000h    ; Point to banked memory area
MVI M, 42h      ; Write to bank 2
MVI A, 00h      ; Load bank 0
OUT 0FFh        ; Switch back to bank 0
```

3. **Read current bank**:
```asm
IN 0FFh         ; Read current bank number into accumulator
```

### Features
- **8 banks**: Total of 288KB addressable memory (32KB fixed + 8 × 32KB banked)
- **Split memory model**: 
  - 0x0000-0x7FFF (32KB): Fixed, non-banked memory for ROM/program code
  - 0x8000-0xFFFF (32KB): Banked memory for data/extended RAM
- **Memory isolation**: Each bank has independent 32KB address space
- **I/O control**: Use standard IN/OUT instructions on port 0xFF
- **API access**: Control banks programmatically via `setBank()` and `getBank()`

### Example Use Cases
- **BIOS development**: Store BIOS routines in bank 0
- **Multi-tasking OS**: Separate memory spaces for different processes
- **Large programs**: Break programs across multiple banks
- **Data storage**: Use banks as extended RAM

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
MOV C, A     ; Copy result to C register
HLT          ; Halt execution
```

The result (8) will be displayed in the **Program Output** section in binary (00001000), hex (0x08), and decimal (8) formats.

## License

Propiatory.
