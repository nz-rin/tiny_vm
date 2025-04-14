## Tiny Stack-Based Virtual Machine

This project is a work in progress.

The main purpose of this project was to improve my personal understanding of memory, instructions and computing.

The Virtual was designed to be modular and expandable and is turing complete.

To use just create an instance for the VM class with a stack_size and memory_size and load instructrions and call run.
__NOTE__ you will have to hand write the binary bytecode since a lexer and language isnt done yet.
or, you can use this as a core and create your own bytecode and lang by changing the headerfiles and some programs.

__The Virtual Machine Currently does not support Strings and only works with u64, i64 and f64 data types.__

# Bytecode
The VM was designed to only work on a fixed instruction and data size to make parsing and developing easier.
Each instruction is represented by a const size_t, typedef'd as Opcode.
Each Opcode is listed in the **vlang.hxx** headerfile under a namespace called **vasm**.
The each bytecode instruction has a corresponding function to call to execute it.

# Executinon
The VM parses an array of opcodes and data and executes it.
This occurs in a loop and runs until an exit opcode or until the last instruction.
The parser reads from the bytecode array, detemines what instruction needs to be called, passing any data types if needed.
After each instruction the parser moves to the next instruction and repeats evaluation and execution.

# Conditionals
Right now the VM has 3 Opcodes to achieve branching, conditional Jump, Uncoditional Jump and a Compare Instruction.
- Compare simply pops two values of the stack and push a flag(result) back on, the type of comparison flags can be found in **vlang.hxx** under **vflag** namespace.
    Currently the supported flags are Equal; Less than; Less than or Equal; Greater than; Greather than or equal and Not Equal.
- Unconditional Jump just pops an address of the stack and jumps to it regardless of flags.
- Coditional Jump is called fjump where f means flag, this works by poping an obsolute address of the stack; Afterwards a Jump condition is popped of the stack,
    a jump condition is represented by the same data type as comparison flag.
    Lastly it pops a flag of the stack that has to be pushed on by a Comparison opcode.
    If the flag meets the jump condition, the execution jumps to the address.
    For this opcode to work the bytecode has to explicityly push a condition and an address on the stack after callling compare.

# Arithmetic
Implementation for basic stack based math is done in the vm_arithmetic.cxx file, results are pushed ontop of the stack.
The VM can add/sub/multiply/divide u64, i64 and f64 only.
This is stack based so 2 values need to be on the stack before and Opcode can be called and the values are poped LHS then RHS.
If pushed in the wrong order divide and subtract will push the wrong answer on the stack;

# Print
The VM comes with 2 utility functions to help debugging.
- dump_stack, prints all the content of the stack in 8 address per row.
- dump_instructions, prints all the instructions of the bytecode as numbers and their address.

# NOTE
This is a work in progress and very well my not work as expected or robustly.

# Compiling
Just include the header fills in /include/ into ur project and use.
This code does include and depend its own logger for print infomation and uses compile flags to conditionally compile certain loged info.
There all the headerfiles in include are required when compiling or externaly intergrating
**Compile with -DDEBUG for more verbose infomation during execusion, -DHEX_ADDR for hex address using for dumping memory**

The main.cxx already has an example of how to use the VM just run ./build.sh --help for more info or use the makefile, running make will print help by default
