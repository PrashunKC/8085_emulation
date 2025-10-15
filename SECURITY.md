# Security Policy

## Supported Versions

This project is currently in active development. Security updates will be applied to the latest version on the `main` branch.

| Version | Supported          |
| ------- | ------------------ |
| Latest (main branch) | :white_check_mark: |
| Older commits | :x: |

## Reporting a Vulnerability

If you discover a security vulnerability in this 8085 Microprocessor Emulator, please report it responsibly:

### How to Report

1. **Do NOT** open a public issue for security vulnerabilities
2. Email the maintainer directly at: [Create an issue with "SECURITY:" prefix if no private contact is available]
3. Include the following information in your report:
   - Description of the vulnerability
   - Steps to reproduce the issue
   - Potential impact
   - Suggested fix (if available)

### What to Expect

- **Initial Response**: You can expect an initial response within 48-72 hours
- **Updates**: Regular updates will be provided as the issue is investigated
- **Resolution**: Once verified, a fix will be developed and released
- **Credit**: Security researchers will be credited (unless they prefer to remain anonymous)

## Security Considerations

This emulator is designed for educational and development purposes. Please be aware of the following:

### Memory Safety

- The emulator allocates 64KB of memory to simulate the 8085's address space
- All memory operations are bounds-checked within the `std::array` container
- User-provided programs are loaded into this isolated memory space

### Input Validation

- The emulator validates opcodes and handles undefined instructions gracefully
- Invalid memory addresses are constrained to the 64KB address space
- No external file loading or network operations are performed in the current version

### Known Limitations

- This is an educational emulator and should not be used for security-critical applications
- The emulator does not implement hardware-level security features
- No authentication or authorization mechanisms are present (as this is a local desktop application)

### Safe Usage Guidelines

1. **Trusted Code Only**: Only load and execute 8085 assembly programs from trusted sources
2. **No Production Use**: This emulator is intended for educational purposes, not production systems
3. **Keep Updated**: Regularly pull the latest changes from the main branch to receive security fixes

## Dependency Security

This project has minimal dependencies:

- **Qt5**: Used for the graphical interface
  - Ensure you use an up-to-date version of Qt5 from official sources
  - Follow Qt's security advisories: https://www.qt.io/product/security
  
- **C++ Standard Library**: Uses C++17 standard library features
  - Keep your compiler toolchain updated

## Build Security

When building from source:

1. Use official package managers (apt, pacman, brew) to install Qt5
2. Verify the integrity of the source code by checking commit signatures
3. Build with a modern, updated C++ compiler (GCC 7+, Clang 5+, MSVC 2017+)

## License

This security policy applies to the 8085 Microprocessor Emulator project, which is licensed under the BSD 3-Clause License. See [LICENSE](LICENSE) for the full license text.
