# risky
A tiny virtual processor with a RISC-inspired instruction set

## Overview
This is an implementation of my own design for a simple, fixed instruction set CPU.

There are only sixteen instructions, all of which are two bytes long regardless of operands. There are four categories of instructions, each category having four instructions.

These categories are as follows:

| Category     | Description                                                                                  |
| ------------ | -------------------------------------------------------------------------------------------- |
| Mathematical | Standard mathematical operations such as addition, subtraction, etc...                       |
| Logical      | Logical operations such as AND, OR, etc...                                                   |
| Memory       | Operations that copy values between registers and RAM or manipulate registers in other ways. |
| Conditional  | Jumps and comparisons for implementing conditional branching.                                |

## Instruction Set

### Mathematical

| Opcode | Instruction Name | Description                                                                                                            |
| ------ | ---------------- | ---------------------------------------------------------------------------------------------------------------------- |
| 0      | ADD              | Adds the values of two given registers, stores result in given register.                                               |
| 1      | SUB              | Subtracts the value of one given register from another, stores result in given register.                               |
| 2      | MUL              | Multiplies the values of two given registers, stores result in given register.                                         |
| 3      | MOD              | Modulo division of one given register from another, stores result in given register.                                   |

### Logical

| Opcode | Instruction Name | Description                                                                                                            |
| ------ | ---------------- | ---------------------------------------------------------------------------------------------------------------------- |
| 4      | AND              | Logical AND two given registers, stores result in given register.                                                      |
| 5      | NOT              | Logical NOT one given register, stores result in given register.                                                       |
| 6      | OR               | Logical OR two given registers, stores result in given register.                                                       |
| 7      | XOR              | Logical XOR two given registers, stores result in given register.                                                      |

### Memory

| Opcode | Instruction Name | Description                                                                                                            |
| ------ | ---------------- | ---------------------------------------------------------------------------------------------------------------------- |
| 8      | SAV              | Stores the value of a given register to a given RAM address                                                            |
| 9      | LOD              | Stores the value of a given RAM address to a given register.                                                           |
| A      | COP              | Copies the value of one given register to another.                                                                     |
| B      | SET              | Sets the value of a given register to an inline literal value.                                                         |

### Conditional

| Opcode | Instruction Name | Description                                                                                                            |
| ------ | ---------------- | ---------------------------------------------------------------------------------------------------------------------- |
| C      | JMP              | Unconditional JUMP to a given RAM address.                                                                             |
| D      | JIF              | Conditional JUMP to a given RAM address if a given register's value is non-zero.                                       |
| E      | EQU              | Compares the values of two given registers for equality, stores result in given register (set to MAX_INT if equal).    |
| F      | GRT              | Compares if the value of one given register is greater than the value of another, stores result as in EQU instruction. |
