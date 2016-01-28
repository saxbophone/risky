#!/usr/bin/env python
"""
RISKY

A tiny virtual processor with a RISC-inspired instruction set

Copyright (c) 2016 Joshua Saxby

See README.md for more information and LICENSE for licensing details.

This program is RASS (Risky ASSembler), a very simple and basic assembler
which will read in files containing instructions in a very simple assembly
format and output executable bitcode which can then be loaded by a program
implementing the RISKY virtual machine.

Currently, this assembly format is very VERY minimal (literally just pneumonics
for the opcodes, because having to write hex is driving me crazy!). At some
point in the future I will probably write a much more sophisticated assembler
that supports features such as labels and other psuedo-opcodes.

Until then, I'm afraid you're on your own! ;)
"""

import sys


OPCODES = {
    'add': 0,
    'sub': 1,
    'mul': 2,
    'mod': 3,
    'and': 4,
    'not': 5,
    'or':  6,
    'xor': 7,
    'sav': 8,
    'lod': 9,
    'cop': 10,
    'set': 11,
    'jmp': 12,
    'jif': 13,
    'equ': 14,
    'grt': 15,
}


def assembly_to_bitcode(assembly):
    """
    Converts an array of an assembly instruction to raw bitcode (bytearray)
    """
    bitcode = bytearray([0, 0])
    # get opcode
    opcode = assembly[0]
    # take care of opcode first
    bitcode[0] |= (OPCODES[opcode] << 4)
    # these opcodes all take 2 or 3 arguments
    if opcode in [
        'add', 'sub', 'mul', 'mod',
        'and', 'not', 'or',  'xor',
        'sav', 'lod', 'cop',
        'jif', 'equ', 'grt',
    ]:
        # fill primary argument
        bitcode[0] |= (int(assembly[1]) % 16)
        # now a operand
        bitcode[1] |= ((int(assembly[2]) % 16) << 4)
        if opcode not in ['not', 'cop',]:
            # now b operand if it's a function that needs it
            bitcode[1] |= (int(assembly[3]) % 16)
    # set has one register, and one literal 8-bit value
    elif opcode == 'set':
        # fill primary argument
        bitcode[0] |= (int(assembly[1]) % 16)
        # fill literal value
        bitcode[1] |= (int(assembly[2]) % 256)
    # jmp takes only a pair of a/b operands
    elif opcode == 'jmp':
        # fill a operand 
        bitcode[1] |= ((int(assembly[1]) % 16) << 4)
        # fill b operand
        bitcode[1] |= (int(assembly[2]) % 16)
    return bitcode


def main(*args):
    # make a new copy of args, minus the first which we don't care for
    options = args[1:]
    if len(options) == 2:
        # the right number of arguments were passed, carry on
        # read in all lines of assembly code file
        with open(options[0]) as input_assembly:
            assembler_code = [
                # split on newlines, and split each line into it's arguments
                line.rstrip('\n').split() for line in input_assembly.readlines()
            ]
        # open output file for binary writing
        with open(options[1], 'wb') as output_bitcode:
            # iterate over each instruction, track instruction count
            instruction_count = 0
            for instruction in assembler_code:
                # convert instruction to bitcode and write to file
                output_bitcode.write(assembly_to_bitcode(instruction))
                # increment instruction count for later use
                instruction_count += 1
            # if instruction count was less than 32768, then we need to pad
            # (each instruction is 2 bytes and we need a 65536 byte file)
            if (instruction_count) < 32768:
                for _ in range(32768 - instruction_count):
                    output_bitcode.write(bytearray([0, 0]))
    else:
        # if there are not two args then we should complain and exit
        print('Usage: rass.py <assembly_input_file.rass> <bitcode_output_file.bin>')
        sys.exit(1)


if __name__ == '__main__':
    main(*sys.argv)
