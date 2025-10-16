# 8085 Microprocessor Emulator

<div align="center">

**A feature-complete graphical emulator for the Intel 8085 microprocessor**

*Built with C++ and Qt5*

</div>

---

## Overview

This project is a fully functional emulator for the Intel 8085 microprocessor, featuring a modern Qt5-based graphical interface. It implements **all 256 opcodes** of the 8085 instruction set, making it suitable for learning, testing 8085 assembly programs, and understanding microprocessor architecture.

## Key Features

- **Complete Instruction Set**: All 246 valid 8085 instructions + 10 undefined opcodes
- **Real-time Register Display**: Monitor A, B, C, D, E, H, L, SP, and PC registers
- **Flag Visualization**: Track S (Sign), Z (Zero), AC (Auxiliary Carry), P (Parity), and CY (Carry) flags
- **Memory Viewer**: Visual representation of the first 256 bytes with PC highlighting
- **Interactive Controls**: Step-by-step execution or continuous run mode
- **Multi-format Output**: View results in binary, hexadecimal, and decimal formats
- **Sample Programs**: Built-in example programs to get started quickly

## Prerequisites

Before building the emulator, ensure you have the following installed:

- **C++ Compiler**: GCC 7+ or Clang 5+ with C++17 support
- **Qt5 Development Libraries**: Qt5 Widgets module
- **Build Tools**: Make or CMake (3.16+)
- **pkg-config**: For locating Qt5 libraries (Linux)

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential qt5-default qtbase5-dev cmake pkg-config
```

**Fedora/RHEL:**
```bash
sudo dnf install gcc-c++ qt5-qtbase-devel cmake pkg-config
```

**macOS (with Homebrew):**
```bash
brew install qt@5 cmake
export PATH="/usr/local/opt/qt@5/bin:$PATH"
```

**Arch Linux:**
```bash
sudo pacman -S base-devel qt5-base cmake
```

## Building

### Option 1: Using Make (Recommended for Quick Builds)

```bash
make
./8085_emulator
```

To clean build artifacts:
```bash
make clean
```

### Option 2: Using CMake (Recommended for Development)

```bash
mkdir build
cd build
cmake ..
make
./8085_emulator
```

### Troubleshooting Build Issues

**Qt5 not found:**
- Ensure Qt5 is installed and `pkg-config` can locate it
- Try: `pkg-config --modversion Qt5Widgets`
- Set `PKG_CONFIG_PATH` if needed: `export PKG_CONFIG_PATH=/path/to/qt5/lib/pkgconfig`

**MOC errors:**
- Make sure Qt5 development tools are installed
- For Make builds, ensure `moc-qt5` is available (or update `Makefile` to use `moc`)

## Usage

### Getting Started

1. **Launch the emulator**: Run the `8085_emulator` executable
2. **Load a program**: Click "Load Program" to load the built-in sample program
3. **Execute code**:
   - **Step**: Execute one instruction at a time (useful for debugging)
   - **Run**: Execute continuously until HLT or manual stop
   - **Stop**: Pause continuous execution
   - **Reset**: Clear CPU state and restart
4. **Monitor execution**: Watch registers, flags, and memory update in real-time
5. **View output**: Check the Program Output panel for formatted results

### Sample Program

The built-in sample program demonstrates basic arithmetic:

```asm
MVI A, 05h   ; Load immediate value 5 into accumulator
MVI B, 03h   ; Load immediate value 3 into B register
ADD B        ; Add B to A (A = A + B = 8)
MOV C, A     ; Copy result from A to C
HLT          ; Halt execution
```

**Expected Result**: The accumulator (A) will contain `0x08` (8 in decimal, `00001000` in binary)

### Memory Viewer

- Displays the first 256 bytes of memory in hexadecimal format
- Current Program Counter (PC) location is highlighted in **yellow**
- Updates in real-time during execution

## Instruction Set Coverage

### 100% COMPLETE - ALL 256 OPCODES IMPLEMENTED!

- **246 valid instructions** fully functional
- **10 undefined opcodes** safely handled (treated as NOP)

### Instruction Categories

| Category | Count | Instructions |
|----------|-------|--------------|
| **Data Transfer** | 64 | MOV, MVI, LXI, LDA, STA, LHLD, SHLD, LDAX, STAX, XCHG |
| **Arithmetic** | 68 | ADD, ADI, ADC, ACI, SUB, SUI, SBB, SBI, INR, DCR, INX, DCX, DAD, DAA |
| **Logical** | 40 | ANA, ANI, XRA, XRI, ORA, ORI, CMP, CPI, RLC, RRC, RAL, RAR, CMA, CMC, STC |
| **Branch** | 46 | JMP, JNZ, JZ, JNC, JC, JPO, JPE, JP, JM, CALL, RET (all variants), RST, PCHL |
| **Stack** | 10 | PUSH, POP, XTHL, SPHL |
| **I/O & Control** | 18 | IN, OUT, EI, DI, RIM, SIM, NOP, HLT |

**Detailed Documentation:**
- [INSTRUCTIONS.md](INSTRUCTIONS.md) - Complete instruction reference with opcodes
- [COMPLETE.md](COMPLETE.md) - Detailed implementation coverage analysis

## Development

### Project Structure

```
8085_emulation/
├── cpu8085.h          # CPU class definition
├── cpu8085.cpp        # CPU implementation and instruction execution
├── gui.cpp            # Qt5 GUI implementation
├── CMakeLists.txt     # CMake build configuration
├── Makefile           # Make build configuration
├── README.md          # This file
├── INSTRUCTIONS.md    # Complete instruction set reference
├── COMPLETE.md        # Implementation coverage details
├── SECURITY.md        # Security policy
└── LICENSE            # BSD-3-Clause license
```

### Extending the Emulator

To add custom functionality or modify instructions:

1. **Modify CPU behavior**: Edit `cpu8085.cpp`
   - Locate the `executeInstruction()` function
   - Instructions are organized by opcode ranges
   - Follow existing patterns for consistency

2. **Add new features to GUI**: Edit `gui.cpp`
   - Uses Qt5 Widgets framework
   - Signals and slots for event handling

3. **Test your changes**:
   - Compile with `make` or `cmake`
   - Load test programs to verify functionality
   - Use Step mode to debug instruction-by-instruction

### Adding Custom Programs

To load your own programs:

1. Edit the `onLoadProgram()` function in `gui.cpp`
2. Create a byte array with your opcodes
3. Use `cpu->loadProgram(program, size, startAddress)`

Example:
```cpp
uint8_t program[] = {
    0x3E, 0x0A,  // MVI A, 0Ah
    0x06, 0x05,  // MVI B, 05h
    0x80,        // ADD B
    0x76         // HLT
};
cpu->loadProgram(program, sizeof(program));
```

## Contributing

Contributions are welcome! Whether it's bug fixes, new features, or documentation improvements:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

Please ensure your code follows the existing style and includes appropriate comments.

## License

This project is licensed under the **BSD-3-Clause License** - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Intel 8085 microprocessor architecture and instruction set
- Qt5 framework for the graphical interface
- The open-source community for tools and resources

## Contact & Support

- **Issues**: [GitHub Issues](https://github.com/PrashunKC/8085_emulation/issues)
- **Security**: See [SECURITY.md](SECURITY.md) for reporting security vulnerabilities

---

<div align="center">

**Made with care for learning and education**

*Star this repository if you find it useful!*

</div>
