# risky [![Build Status](https://travis-ci.org/saxbophone/risky.svg?branch=develop)](https://travis-ci.org/saxbophone/risky)
A tiny virtual processor with a RISC-inspired instruction set

> **Note**: This is my second attempt at writing a minimalist VM.

> The first attempt is in this project's Git history and can be found at the [prototype](https://github.com/saxbophone/risky/tree/prototype) tag.

## Why?
A couple of years ago I started building an 8-Bit CPU in the popular sandbox building game *Minecraft*. I got about as far as building the arithmetic logic unit (ALU) and then gave up. However, the idea stuck with me and I decided that if I were to give it another go, I should carefully plan out the design of the CPU first and write an emulator to prototype it.

I did this and the results can be found at the link to the prototype at the top of this README. However, the result was far from perfect and really too minimalistic to be of much use. I was quite seriously limiting myself by only allowing for 16 instructions, and manipulating 64KiB of memory with 8-bit indexes is rather unwieldy.

So, this is the new version of **RISKY**, currently under development and aiming towards a version 1 release goal. I haven't finalised all the details yet, but it will most likely be a 16-bit machine with more instructions than the prototype. Regardless of this the aim will still be to keep it as minimal and well-rounded as possible, the idea being that it should be designed to be as easy to create a simulated hardware version of the machine (in Minecraft or in a piece of electronics simulation software) as possible.

## Plan
Here I will outline the planned design or **RISKY**

### Instruction Glossary
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

### Instruction Categories
Instructions fall into one of 5 different groups, and all groups except **Memory Operations** also have a *basic* and an *advanced* sub-group.

| Instruction Group Name | Basic Set       | Advanced Set    |
| ---------------------- | --------------- | --------------- |
| Arithmetic Operations  | ADD SUB MLT DIV | INC DEC MOD     |
| Logical Operations     | OR NOT AND XOR  | LSH RSH ROT     |
| Comparisons            | EQU NEQ GTN LTN | GEQ LEQ         |
| Flow Control           | NOP JMP BRA HLT | RIT SLP INT CLR |
| Memory Operations      | SET COP LOD SAV |                 |

## License
This version and all future versions of the software will be licensed under the **Mozilla Public License v2.0**, a copy of which can be found in the file named [LICENSE](https://raw.githubusercontent.com/saxbophone/risky/master/LICENSE) in the root directory of this repository.

> **Note**: I'd previously licensed the prototype under the MIT license and then under v3.0 of the GNU GPL.

**MORE COMING SOON**
