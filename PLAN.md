# Plan
This document will outline the planned design of **RISKY**

## Instruction Glossary
It is planned that there will be 32 instructions. Instructions fall into one of 8 different groups. Each group contains 4 instructions.

Here is a series of tables for these groups, each containing mnemonics and brief descriptions of the group's instructions.

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
| INC                  | Increment a value                                                    |
| DEC                  | Decrement a value                                                    |
| MOD                  | Perform modulo division of one value by another                      |
| QOP                  | Query last Operations (for overflow, underflow, divide by zero, etc) |

### Bitwise Logical Operations

| Instruction Mnemonic | Description                     |
| -------------------- | ------------------------------- |
| EOR                  | Bitwise OR two values together  |
| NOT                  | Bitwise NOT one value           |
| AND                  | Bitwise AND two values together |
| XOR                  | Bitwise XOR two values together |

### Bit Manipulation Operations

| Instruction Mnemonic | Description                            |
| -------------------- | -------------------------------------- |
| LSH                  | Shift the bits of a value to the left  |
| RSH                  | Shift the bits of a value to the right |
| ROT                  | Rotate the bits of a value             |
| CAS                  | Cascade the bits of a value            |

### Comparisons

| Instruction Mnemonic | Description                                  |
| -------------------- | -------------------------------------------- |
| EQU                  | Compare two values for equality              |
| NEQ                  | Compare two values for inequality            |
| GTN                  | Compare if one value is greater than another |
| LTN                  | Compare if one value is less than another    |

### Flow Control

| Instruction Mnemonic | Description                                |
| -------------------- | ------------------------------------------ |
| NOP                  | No-Op, Do nothing                          |
| JMP                  | Unconditional jump to a new memory address |
| BRA                  | Conditional jump to a new memory address   |
| HLT                  | Halt, completely stop the CPU              |

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
