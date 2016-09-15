# Plan
This document will outline the planned design of **RISKY**

## Instruction Glossary
It is planned that there will be 32 instructions. Here is a table of instruction mnemonics and a brief description of each.

| Instruction Mnemonic | Description                                              |
| -------------------- | -------------------------------------------------------- |
| ADD                  | Add two values together                                  |
| SUB                  | Subtract one value from another                          |
| MLT                  | Multiply two values together                             |
| DIV                  | Divide one value by another                              |
| INC                  | Increment a value                                        |
| DEC                  | Decrement a value                                        |
| MOD                  | Perform modulo division of one value by another          |
| XX0                  | Undefined Instruction 0                                  |
| EOR                  | Bitwise OR two values together                           |
| NOT                  | Bitwise NOT one value                                    |
| AND                  | Bitwise AND two values together                          |
| XOR                  | Bitwise XOR two values together                          |
| LSH                  | Shift the bits of a value to the left                    |
| RSH                  | Shift the bits of a value to the right                   |
| ROT                  | Rotate the bits of a value                               |
| CAS                  | Cascade the bits of a value                              |
| EQU                  | Compare two values for equality                          |
| NEQ                  | Compare two values for inequality                        |
| GTN                  | Compare if one value is greater than another             |
| LTN                  | Compare if one value is less than another                |
| NOP                  | No-Op, Do nothing                                        |
| JMP                  | Unconditional jump to a new memory address               |
| BRA                  | Conditional jump to a new memory address                 |
| HLT                  | Halt, completely stop the CPU                            |
| SET                  | Set the value of a register to a literal value           |
| COP                  | Copy the value of one register to another                |
| LOD                  | Load a value from memory to a register                   |
| SAV                  | Save the value of a register to memory                   |
| XX1                  | Undefined Instruction 1                                  |
| XX2                  | Undefined Instruction 2                                  |
| XX3                  | Undefined Instruction 3                                  |
| XX4                  | Undefined Instruction 4                                  |

## Instruction Categories
Instructions fall into one of 8 different groups. Each group contains 4 instructions.

| Instruction Group Name         | Instructions    |
| ------------------------------ | --------------- |
| Arithmetic Operations          | ADD SUB MLT DIV |
| Extended Arithmetic Operations | INC DEC MOD ??? |
| Logical Operations             | EOR NOT AND XOR |
| Bit Manipulation Operations    | LSH RSH ROT CAS |
| Comparisons                    | EQU NEQ GTN LTN |
| Flow Control                   | NOP JMP BRA HLT |
| Memory Operations              | SET COP LOD SAV |
| Undefined Group 0              | XX1 XX2 XX3 XX4 |
