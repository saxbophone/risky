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
| OR                   | Bitwise OR two values together                           |
| NOT                  | Bitwise NOT one value                                    |
| AND                  | Bitwise AND two values together                          |
| XOR                  | Bitwise XOR two values together                          |
| LSH                  | Shift the bits of a value to the left                    |
| RSH                  | Shift the bits of a value to the right                   |
| ROT                  | Rotate the bits of a value                               |
| EQU                  | Compare two values for equality                          |
| NEQ                  | Compare two values for inequality                        |
| GTN                  | Compare if one value is greater than another             |
| LTN                  | Compare if one value is less than another                |
| GEQ                  | Compare if one value is greater than or equal to another |
| LEQ                  | Compare if one value is less than or equal to another    |
| NOP                  | No-Op, Do nothing                                        |
| JMP                  | Unconditional jump to a new memory address               |
| BRA                  | Conditional jump to a new memory address                 |
| HLT                  | Halt, completely stop the CPU                            |
| RIT                  | Register an interrupt handler                            |
| SLP                  | Put CPU into sleep mode (recoverable by interrupt)       |
| INT                  | Manually trigger an interrupt                            |
| CLR                  | Clear a registered interrupt handler                     |
| SET                  | Set the value of a register to a literal value           |
| COP                  | Copy the value of one register to another                |
| LOD                  | Load a value from memory to a register                   |
| SAV                  | Save the value of a register to memory                   |

## Instruction Categories
Instructions fall into one of 5 different groups and all groups except **Memory Operations** also have a *basic* and an *advanced* sub-group.

| Instruction Group Name | Basic Set       | Advanced Set    |
| ---------------------- | --------------- | --------------- |
| Arithmetic Operations  | ADD SUB MLT DIV | INC DEC MOD     |
| Logical Operations     | OR NOT AND XOR  | LSH RSH ROT     |
| Comparisons            | EQU NEQ GTN LTN | GEQ LEQ         |
| Flow Control           | NOP JMP BRA HLT | RIT SLP INT CLR |
| Memory Operations      | SET COP LOD SAV |                 |
