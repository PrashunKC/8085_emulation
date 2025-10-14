# 8085 Instruction Set - Complete Implementation

## Data Transfer Group

### MOV - Move Register to Register (49 instructions)
- **MOV r1, r2** - Copy register r2 to r1
- **MOV r, M** - Copy memory (HL) to register
- **MOV M, r** - Copy register to memory (HL)
- All 64 combinations (except MOV M, M which is HLT)

### MVI - Move Immediate (8 instructions)
- **MVI r, data** - Load 8-bit immediate data to register
- **MVI M, data** - Load 8-bit immediate data to memory (HL)
- Opcodes: 06, 0E, 16, 1E, 26, 2E, 36, 3E

### LXI - Load Register Pair Immediate (4 instructions)
- **LXI B, data16** (0x01) - Load BC with 16-bit data
- **LXI D, data16** (0x11) - Load DE with 16-bit data
- **LXI H, data16** (0x21) - Load HL with 16-bit data
- **LXI SP, data16** (0x31) - Load SP with 16-bit data

### Load/Store Accumulator
- **LDA addr** (0x3A) - Load A from memory address
- **STA addr** (0x32) - Store A to memory address
- **LHLD addr** (0x2A) - Load HL from memory address
- **SHLD addr** (0x22) - Store HL to memory address
- **LDAX B** (0x0A) - Load A from address in BC
- **LDAX D** (0x1A) - Load A from address in DE
- **STAX B** (0x02) - Store A to address in BC
- **STAX D** (0x12) - Store A to address in DE

### Exchange
- **XCHG** (0xEB) - Exchange DE and HL

## Arithmetic Group

### Addition
- **ADD r** (0x80-0x87) - Add register to A
- **ADD M** (0x86) - Add memory (HL) to A
- **ADI data** (0xC6) - Add immediate to A
- **ADC r** (0x88-0x8F) - Add register to A with carry
- **ADC M** (0x8E) - Add memory to A with carry
- **ACI data** (0xCE) - Add immediate to A with carry

### Subtraction
- **SUB r** (0x90-0x97) - Subtract register from A
- **SUB M** (0x96) - Subtract memory from A
- **SUI data** (0xD6) - Subtract immediate from A
- **SBB r** (0x98-0x9F) - Subtract register from A with borrow
- **SBB M** (0x9E) - Subtract memory from A with borrow
- **SBI data** (0xDE) - Subtract immediate from A with borrow

### Increment/Decrement
- **INR r** (0x04, 0x0C, 0x14, 0x1C, 0x24, 0x2C, 0x3C) - Increment register
- **INR M** (0x34) - Increment memory (HL)
- **DCR r** (0x05, 0x0D, 0x15, 0x1D, 0x25, 0x2D, 0x3D) - Decrement register
- **DCR M** (0x35) - Decrement memory (HL)
- **INX rp** (0x03, 0x13, 0x23, 0x33) - Increment register pair
- **DCX rp** (0x0B, 0x1B, 0x2B, 0x3B) - Decrement register pair

### Double Add
- **DAD B** (0x09) - Add BC to HL
- **DAD D** (0x19) - Add DE to HL
- **DAD H** (0x29) - Add HL to HL (double HL)
- **DAD SP** (0x39) - Add SP to HL

### Special
- **DAA** (0x27) - Decimal Adjust Accumulator

## Logical Group

### AND Operations
- **ANA r** (0xA0-0xA7) - AND register with A
- **ANA M** (0xA6) - AND memory with A
- **ANI data** (0xE6) - AND immediate with A

### XOR Operations
- **XRA r** (0xA8-0xAF) - XOR register with A
- **XRA M** (0xAE) - XOR memory with A
- **XRI data** (0xEE) - XOR immediate with A

### OR Operations
- **ORA r** (0xB0-0xB7) - OR register with A
- **ORA M** (0xB6) - OR memory with A
- **ORI data** (0xF6) - OR immediate with A

### Compare
- **CMP r** (0xB8-0xBF) - Compare register with A
- **CMP M** (0xBE) - Compare memory with A
- **CPI data** (0xFE) - Compare immediate with A

### Rotate
- **RLC** (0x07) - Rotate A left
- **RRC** (0x0F) - Rotate A right
- **RAL** (0x17) - Rotate A left through carry
- **RAR** (0x1F) - Rotate A right through carry

### Complement
- **CMA** (0x2F) - Complement A (1's complement)
- **CMC** (0x3F) - Complement carry flag
- **STC** (0x37) - Set carry flag

## Branch Group

### Jump
- **JMP addr** (0xC3) - Unconditional jump
- **JNZ addr** (0xC2) - Jump if not zero
- **JZ addr** (0xCA) - Jump if zero
- **JNC addr** (0xD2) - Jump if no carry
- **JC addr** (0xDA) - Jump if carry
- **JPO addr** (0xE2) - Jump if parity odd
- **JPE addr** (0xEA) - Jump if parity even
- **JP addr** (0xF2) - Jump if positive
- **JM addr** (0xFA) - Jump if minus

### Call
- **CALL addr** (0xCD) - Unconditional call
- **CNZ addr** (0xC4) - Call if not zero
- **CZ addr** (0xCC) - Call if zero
- **CNC addr** (0xD4) - Call if no carry
- **CC addr** (0xDC) - Call if carry
- **CPO addr** (0xE4) - Call if parity odd
- **CPE addr** (0xEC) - Call if parity even
- **CP addr** (0xF4) - Call if positive
- **CM addr** (0xFC) - Call if minus

### Return
- **RET** (0xC9) - Unconditional return
- **RNZ** (0xC0) - Return if not zero
- **RZ** (0xC8) - Return if zero
- **RNC** (0xD0) - Return if no carry
- **RC** (0xD8) - Return if carry
- **RPO** (0xE0) - Return if parity odd
- **RPE** (0xE8) - Return if parity even
- **RP** (0xF0) - Return if positive
- **RM** (0xF8) - Return if minus

### Restart (RST)
- **RST 0** (0xC7) - Call 0x0000
- **RST 1** (0xCF) - Call 0x0008
- **RST 2** (0xD7) - Call 0x0010
- **RST 3** (0xDF) - Call 0x0018
- **RST 4** (0xE7) - Call 0x0020
- **RST 5** (0xEF) - Call 0x0028
- **RST 6** (0xF7) - Call 0x0030
- **RST 7** (0xFF) - Call 0x0038

### Special Jump
- **PCHL** (0xE9) - Move HL to PC (jump to address in HL)

## Stack Operations

### Push
- **PUSH B** (0xC5) - Push BC onto stack
- **PUSH D** (0xD5) - Push DE onto stack
- **PUSH H** (0xE5) - Push HL onto stack
- **PUSH PSW** (0xF5) - Push A and flags onto stack

### Pop
- **POP B** (0xC1) - Pop BC from stack
- **POP D** (0xD1) - Pop DE from stack
- **POP H** (0xE1) - Pop HL from stack
- **POP PSW** (0xF1) - Pop A and flags from stack

### Stack Manipulation
- **XTHL** (0xE3) - Exchange HL with top of stack
- **SPHL** (0xF9) - Move HL to SP

## I/O and Machine Control

### I/O
- **IN port** (0xDB) - Read from I/O port (simplified)
- **OUT port** (0xD3) - Write to I/O port (simplified)

### Interrupts
- **EI** (0xFB) - Enable interrupts
- **DI** (0xF3) - Disable interrupts

### 8085 Specific
- **RIM** (0x20) - Read Interrupt Mask
- **SIM** (0x30) - Set Interrupt Mask

### Control
- **NOP** (0x00) - No operation
- **HLT** (0x76) - Halt CPU

## Total Instructions Implemented

- **246 instructions** covering the complete 8085 instruction set
- All addressing modes supported
- All flags properly implemented (S, Z, AC, P, CY)
- Stack operations fully functional
- Conditional jumps, calls, and returns working

## Notes

- I/O instructions (IN/OUT) are simplified (no actual I/O)
- RIM/SIM are simplified (basic implementation)
- All arithmetic and logical operations update flags correctly
- Memory addressing through register pairs fully supported
