# risky [![Build Status](https://travis-ci.org/saxbophone/risky.svg?branch=master)](https://travis-ci.org/saxbophone/risky)
A tiny virtual processor with a RISC-inspired instruction set

> **Note**: This is my second attempt at writing a minimalist VM.

> The first attempt is in this project's Git history and can be found at the [prototype](https://github.com/saxbophone/risky/tree/prototype) tag.

## Why?
A couple of years ago I started building an 8-Bit CPU in the popular sandbox building game *Minecraft*. I got about as far as building the arithmetic logic unit (ALU) and then gave up. However, the idea stuck with me and I decided that if I were to give it another go, I should carefully plan out the design of the CPU first and write an emulator to prototype it.

I did this and the results can be found at the link to the prototype at the top of this README. However, the result was far from perfect and really too minimalistic to be of much use. I was quite seriously limiting myself by only allowing for 16 instructions, and manipulating 64KiB of memory with 8-bit indexes is rather unwieldy.

So, this is the new version of **RISKY**, currently under development and aiming towards a version 1 release goal. I haven't finalised all the details yet, but it will most likely be a 16-bit machine with more instructions than the prototype. Regardless of this the aim will still be to keep it as minimal and well-rounded as possible, the idea being that it should be designed to be as easy to create a simulated hardware version of the machine (in Minecraft or in a piece of electronics simulation software) as possible.

## License
This version and all future versions of the software will be licensed under the **Moziall Public License v2.0**, a copy of which can be found in the file named [LICENSE](https://raw.githubusercontent.com/saxbophone/risky/master/LICENSE) in the root directory of this repository.

> **Note**: I'd previously licensed the prototype under the MIT license and then under v3.0 of the GNU GPL.

**MORE COMING SOON**
