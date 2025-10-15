# Bank Switching Guide

This document provides a comprehensive guide to using bank switching in the 8085 emulator.

## Overview

The emulator implements a bank switching scheme that extends the 8085's 64KB address space to 288KB total addressable memory. This is achieved by dividing the address space into two regions:

- **0x0000-0x7FFF (32KB)**: Fixed, non-banked memory for ROM/program code
- **0x8000-0xFFFF (32KB)**: Banked memory for data/extended RAM (8 banks available)

## Memory Layout

```
┌──────────────────────┐ 0x0000
│                      │
│   Fixed Memory       │
│   (Program/ROM)      │
│   32KB               │
│   Non-banked         │
│                      │
├──────────────────────┤ 0x8000
│                      │
│   Banked Memory      │
│   (Data/RAM)         │
│   32KB per bank      │
│   8 banks (0-7)      │
│                      │
└──────────────────────┘ 0xFFFF
```

## Using Bank Switching in Assembly

### Switching Banks

Use the `OUT` instruction to switch banks:

```asm
; Switch to bank 2
MVI A, 02h      ; Load bank number into accumulator
OUT 0FFh        ; Switch to bank 2

; Now all memory accesses to 0x8000-0xFFFF use bank 2
```

### Reading Current Bank

Use the `IN` instruction to read the current bank:

```asm
IN 0FFh         ; Read current bank into accumulator
```

### Example: Multi-Bank Data Storage

```asm
; Store different data in each bank
MVI B, 00h      ; Start with bank 0

STORE_LOOP:
    MOV A, B        ; Bank number to A
    OUT 0FFh        ; Switch to bank
    
    ; Store bank number at 0x8000
    LXI H, 8000h
    MOV M, B
    
    ; Next bank
    INR B
    MVI A, 08h
    CMP B
    JNZ STORE_LOOP

; Read back from bank 3
MVI A, 03h
OUT 0FFh
LXI H, 8000h
MOV A, M        ; A now contains 0x03
```

## Using Bank Switching in C++

### Enable Bank Switching

```cpp
CPU8085 cpu;
cpu.enableBankSwitching(true);
```

### Switch Banks Programmatically

```cpp
// Write to different banks
for (int bank = 0; bank < cpu.getBankCount(); bank++) {
    cpu.setBank(bank);
    cpu.setMemory(0x8000, 0x10 + bank);
}

// Read from specific bank
cpu.setBank(3);
uint8_t value = cpu.getMemory(0x8000);  // Gets value from bank 3
```

### Check Current Bank

```cpp
uint8_t currentBank = cpu.getBank();
uint8_t totalBanks = cpu.getBankCount();  // Returns 8
```

## Use Cases

### 1. BIOS Development

Store BIOS routines in the fixed memory area (0x0000-0x7FFF) and use banked memory for:
- System variables and buffers
- Device drivers data
- User program space

```asm
; BIOS in fixed memory
ORG 0000h
BIOS_INIT:
    ; Initialize system
    MVI A, 00h
    OUT 0FFh        ; Use bank 0 for system data
    ; ... more BIOS code ...
```

### 2. Multi-Tasking OS

Assign each task its own memory bank:

```cpp
// Task 0 in bank 0
cpu.setBank(0);
cpu.loadProgram(task0_code, task0_size, 0x0100);

// Task 1 in bank 1
cpu.setBank(1);
cpu.loadProgram(task1_code, task1_size, 0x0100);

// Switch between tasks
cpu.setBank(currentTask);
```

### 3. Large Data Processing

Use banks as extended RAM for large datasets:

```asm
; Process 256KB of data across 8 banks
MVI B, 00h      ; Bank counter

PROCESS_BANKS:
    MOV A, B
    OUT 0FFh        ; Switch to bank
    
    ; Process 32KB in current bank
    CALL PROCESS_DATA
    
    INR B
    MVI A, 08h
    CMP B
    JNZ PROCESS_BANKS
```

### 4. Bank-Switching Graphics

Store multiple screens or tilesets in different banks:

```asm
; Load tileset from bank 2
MVI A, 02h
OUT 0FFh
LXI H, 8000h    ; Point to tileset data

; Copy to display memory
LXI D, A000h
MVI B, 00h
COPY_LOOP:
    MOV A, M
    STAX D
    INX H
    INX D
    DCR B
    JNZ COPY_LOOP
```

## Best Practices

1. **Keep code in fixed memory**: Always place executable code in the 0x0000-0x7FFF range
2. **Use banked memory for data**: Store large data structures, buffers, and variables in 0x8000-0xFFFF
3. **Document bank usage**: Keep track of which banks are used for what purpose
4. **Minimize bank switches**: Bank switching has overhead; batch operations when possible
5. **Save and restore banks**: If your routine switches banks, restore the original bank before returning

## Example: Complete Bank-Switched Program

```asm
; Example program demonstrating bank switching
ORG 0000h

START:
    ; Initialize - use bank 0 for system data
    MVI A, 00h
    OUT 0FFh
    
    ; Store "Hello" in bank 0
    LXI H, 8000h
    MVI M, 'H'
    INX H
    MVI M, 'e'
    INX H
    MVI M, 'l'
    INX H
    MVI M, 'l'
    INX H
    MVI M, 'o'
    
    ; Store "World" in bank 1
    MVI A, 01h
    OUT 0FFh
    LXI H, 8000h
    MVI M, 'W'
    INX H
    MVI M, 'o'
    INX H
    MVI M, 'r'
    INX H
    MVI M, 'l'
    INX H
    MVI M, 'd'
    
    ; Read from both banks
    MVI A, 00h
    OUT 0FFh
    LXI H, 8000h
    MOV B, M        ; B = 'H'
    
    MVI A, 01h
    OUT 0FFh
    LXI H, 8000h
    MOV C, M        ; C = 'W'
    
    HLT

; Subroutine: Copy data between banks
COPY_BANK:
    ; Inputs: B = source bank, C = dest bank
    ; Copies 256 bytes from 0x8000 in source to 0x8000 in dest
    PUSH B
    PUSH D
    PUSH H
    
    MOV A, B
    OUT 0FFh        ; Switch to source bank
    LXI H, 8000h
    LXI D, 7F00h    ; Temp buffer in fixed memory
    MVI B, 00h
COPY_TO_TEMP:
    MOV A, M
    STAX D
    INX H
    INX D
    DCR B
    JNZ COPY_TO_TEMP
    
    MOV A, C
    OUT 0FFh        ; Switch to dest bank
    LXI H, 8000h
    LXI D, 7F00h
    MVI B, 00h
COPY_FROM_TEMP:
    LDAX D
    MOV M, A
    INX H
    INX D
    DCR B
    JNZ COPY_FROM_TEMP
    
    POP H
    POP D
    POP B
    RET
```

## Testing Bank Switching

The emulator includes a comprehensive test program (`bank_switching_test.cpp`) that validates:

1. Basic bank switching via API
2. Bank switching via I/O instructions (IN/OUT)
3. Memory isolation between banks

Run the test with:
```bash
g++ -std=c++17 -o bank_switching_test bank_switching_test.cpp cpu8085.cpp
./bank_switching_test
```

## Technical Details

- **Bank switching port**: 0xFF (255)
- **Number of banks**: 8 (0-7)
- **Bank size**: 32KB (0x8000 bytes)
- **Total banked memory**: 256KB (8 × 32KB)
- **Fixed memory**: 32KB (0x0000-0x7FFF)
- **Total addressable**: 288KB (32KB + 256KB)

## Limitations

1. Only addresses 0x8000-0xFFFF are bank-switched
2. Maximum 8 banks supported
3. Bank switching applies only when enabled via `enableBankSwitching(true)`
4. Instruction fetches always occur from main memory (fixed area)
5. Stack operations in banked area (SP >= 0x8000) will use current bank

## See Also

- [README.md](README.md) - Main documentation
- [bank_switching_test.cpp](bank_switching_test.cpp) - Test program with examples
- [INSTRUCTIONS.md](INSTRUCTIONS.md) - Complete instruction set reference
