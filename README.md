# risky
A tiny virtual processor with a RISC-inspired instruction set

## Overview
This is an implementation of my own design for a simple, fixed instruction set CPU.

There are only sixteen instructions, all of which are two bytes long regardless of operands.

The CPU can handle 8-bit unsigned integers only. As a result, it can address up to 256 bytes of RAM. This could be extended to 16-bit integers and then being able to address up to 64K of RAM. This could be done by doubling the size of the part of the instruction used for RAM addressing (lengthening the instruction size to three bytes). To make sure this space is not completely wasted, instructions that operate on registers could be parallelised to operate on two sets at once, perhaps.

## Instruction Categories

There are four categories of instructions, each category having four instructions.

These categories are as follows:

| Category     | Description                                                                                  |
| ------------ | -------------------------------------------------------------------------------------------- |
| Mathematical | Standard mathematical operations such as addition, subtraction, etc...                       |
| Logical      | Logical operations such as AND, OR, etc...                                                   |
| Memory       | Operations that copy values between registers and RAM or manipulate registers in other ways. |
| Conditional  | Jumps and comparisons for implementing conditional branching.                                |

## Instruction Format

Each instruction is two bytes long, and starts with a 4-bit Opcode.

The next 4 bits are always used for a register's address (there are 16 registers). This register is the result register for mathematical, logical or comparitive operations and the source/destination register for operations that copy to/from memory.

The final 8 bits are used differently depending on what the instruction is:

If the instruction is mathematical, logical or comparative, then the final 8 bits are split into two 4-bit register addresses. These are the operands of the operation (NOT only has one operand, which uses the first 4 bits only).

If the instruction is SAV or LOD (save/load), then the last 8 bits are the memory address to read from/to.

If the instruction is COP, then like NOT only the first 4 bits of the 8 remaining bits are used, and this is a register address.

If the instruction is SET, then the final 8 bits are a literal unsigned integer value, which is used by this instruction.

Finally, if the instruction is JMP or JIF, then the last 8 bits are the RAM address to jump to.

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
