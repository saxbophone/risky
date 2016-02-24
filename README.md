# risky
A tiny virtual processor with a RISC-inspired instruction set

## Why?

A couple of years ago I started building an 8-Bit CPU in the popular sandbox building game *Minecraft*. I got about as far as building the arithmetic logic unit (ALU) and then gave up. However, the idea stuck with me and I decided that if I were to give it another go, I should carefully plan out the design of the CPU first and write an emulator to prototype it, before taking pixellated pickaxe to pixellated block and building the damn thing in Minecraft.

**RISKY** is that prototype. It is by no means perfect, and I sacrificed a lot in the way of convention and practicality to keep it as minimal and *pure* as possible for ease of building (although how much it ticks either of those boxes is left as an open question).

> I haven't yet built **RISKY** in Minecraft, as I have not yet finalised the design but I will update this repo with a download link for the world save if I get round to building it. :wrench:

## Overview
This is an implementation of my own design for a simple, fixed instruction set CPU.

There are only sixteen instructions, all of which are two bytes long regardless of operands.

The CPU can handle 8-bit unsigned integers only. It can address up to 64KiB (*kibibytes*) of RAM by using two bytes for addressing purposes (equivalent to an 8-bit CPU with a 16-bit data bus I guess). RAM is addressed by passing in the addresses of two registers, which between them make up the two bytes needed to address RAM. 

**Note:** In all cases (register addresses, RAM addresses, opcodes and literal values) all integers are unsigned and are Big-Endian.

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

If the instruction is mathematical, logical, comparative one of **`SAV`**, **`LOD`**, **`JMP`** or **`JIF`**, then the final 8 bits are split into two 4-bit register addresses. These are the operands of the operation (**`NOT`** only has one operand, which uses the first 4 bits only). With RAM or JUMP operations, the operands are used to do the addressing.

If the instruction is **`COP`**, then like **`NOT`** only the first 4 bits of the 8 remaining bits are used, and this is a register address.

If the instruction is **`SET`**, then the final 8 bits are a literal unsigned integer value, which is used by this instruction.

## Instruction Set

### Mathematical

| Opcode | Instruction Name | Description                                                                                                            |
| ------ | ---------------- | ---------------------------------------------------------------------------------------------------------------------- |
| 0      | **`ADD`**        | Adds the values of two given registers, stores result in given register.                                               |
| 1      | **`SUB`**        | Subtracts the value of one given register from another, stores result in given register.                               |
| 2      | **`MUL`**        | Multiplies the values of two given registers, stores result in given register.                                         |
| 3      | **`MOD`**        | Modulo division of one given register from another, stores result in given register.                                   |

### Logical

| Opcode | Instruction Name | Description                                                                                                            |
| ------ | ---------------- | ---------------------------------------------------------------------------------------------------------------------- |
| 4      | **`AND`**        | Logical AND two given registers, stores result in given register.                                                      |
| 5      | **`NOT`**        | Logical NOT one given register, stores result in given register.                                                       |
| 6      | **`OR`**         | Logical OR two given registers, stores result in given register.                                                       |
| 7      | **`XOR`**        | Logical XOR two given registers, stores result in given register.                                                      |

### Memory

| Opcode | Instruction Name | Description                                                                                                            |
| ------ | ---------------- | ---------------------------------------------------------------------------------------------------------------------- |
| 8      | **`SAV`**        | Stores the value of a given register to a given RAM address                                                            |
| 9      | **`LOD`**        | Stores the value of a given RAM address to a given register.                                                           |
| A      | **`COP`**        | Copies the value of one given register to another.                                                                     |
| B      | **`SET`**        | Sets the value of a given register to an inline literal value.                                                         |

### Conditional

| Opcode | Instruction Name | Description                                                                                                            |
| ------ | ---------------- | ---------------------------------------------------------------------------------------------------------------------- |
| C      | **`JMP`**        | Unconditional JUMP to a given RAM address.                                                                             |
| D      | **`JIF`**        | Conditional JUMP to a given RAM address if a given register's value is non-zero.                                       |
| E      | **`EQU`**        | Compares the values of two given registers for equality, stores result in given register (set to MAX_INT if equal).    |
| F      | **`GRT`**        | Compares if the value of one given register is greater than the value of another, stores result as in EQU instruction. |
