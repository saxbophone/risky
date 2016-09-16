# Plan
This document will outline the planned design of **RISKY**

## Data format
**RISKY** will be a 16-bit virtual machine, capable of performing operations on both 8-bit or 16-bit unsigned integers. It will not support floating point or signed arithmetic.

**RISKY** will have 256 16-bit registers available to it for general-purpose use by assembly code running on it. No *special* registers such as the stack pointer will be directly accessible for manipulation or reading.

All integers are big-endian, both in-machine and in bytecode.

## Instruction format
All instructions for **RISKY** are fixed-length and are 4 bytes long each.

The first 5 bits of the first byte are the instruction opcode (this is further broken down into 3 bits for the instruction group and 2 bits for the instruction number within that group).

The remaining 3 bits of the first byte are flags, and used differently for different types of instruction.

The second byte is the number of the recipient register for the result of an operation (or the channel number when writing data out), with the exception of the SAV instruction, where it refers to the register to read data from.

The remaining two bytes are used either as the numbers of the operand registers for an operation, or used as a literal 16-bit value (for setting register values, or as a RAM address).

## Instruction Glossary
It is planned that there will be 32 instructions. Instructions fall into one of 8 different groups. Each group contains 4 instructions.

Here is a series of tables for these groups, each containing mnemonics and brief descriptions of the group's instructions.

### Flow Control

| Instruction Mnemonic | Description                                |
| -------------------- | ------------------------------------------ |
| NOP                  | No-Op, Do nothing                          |
| JMP                  | Unconditional jump to a new memory address |
| BRA                  | Conditional jump to a new memory address   |
| HLT                  | Halt, completely stop the CPU              |

### Comparisons

| Instruction Mnemonic | Description                                  |
| -------------------- | -------------------------------------------- |
| EQU                  | Compare two values for equality              |
| NEQ                  | Compare two values for inequality            |
| GTN                  | Compare if one value is greater than another |
| LTN                  | Compare if one value is less than another    |

### Arithmetic Operations

| Instruction Mnemonic | Description                     |
| -------------------- | ------------------------------- |
| ADD                  | Add two values together         |
| SUB                  | Subtract one value from another |
| MLT                  | Multiply two values together    |
| DIV                  | Divide one value by another     |

### Extended Arithmetic Operations

| Instruction Mnemonic | Description                                                          |
| -------------------- | -------------------------------------------------------------------- |
| MOD                  | Perform modulo division of one value by another                      |
| INC                  | Increment a value                                                    |
| DEC                  | Decrement a value                                                    |
| QOP                  | Query last Operations (for overflow, underflow, divide by zero, etc) |

### Bitwise Logical Operations

| Instruction Mnemonic | Description                     |
| -------------------- | ------------------------------- |
| EOR                  | Bitwise OR two values together  |
| AND                  | Bitwise AND two values together |
| XOR                  | Bitwise XOR two values together |
| NOT                  | Bitwise NOT one value           |

### Bit Manipulation Operations

| Instruction Mnemonic | Description                            |
| -------------------- | -------------------------------------- |
| LSH                  | Shift the bits of a value to the left  |
| RSH                  | Shift the bits of a value to the right |
| ROT                  | Rotate the bits of a value             |
| CAS                  | Cascade the bits of a value            |

### Memory Operations

| Instruction Mnemonic | Description                                    |
| -------------------- | ---------------------------------------------- |
| SET                  | Set the value of a register to a literal value |
| COP                  | Copy the value of one register to another      |
| LOD                  | Load a value from memory to a register         |
| SAV                  | Save the value of a register to memory         |

### Input / Output

| Instruction Mnemonic | Description                     |
| -------------------- | ------------------------------- |
| QDC                  | Query state of Data Channel     |
| CDC                  | Configure state of Data Channel |
| REA                  | Read data channel to register   |
| WRI                  | Write register to data channel  |
