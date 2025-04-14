#ifndef VLANG_HXX
#define VLANG_HXX

#include <cstddef>
namespace vasm{

	typedef const size_t Opcode;

	static Opcode PUSH 	= 0;
	static Opcode CMP 	= 1;
	static Opcode JMP 	= 2;
	static Opcode FJMP 	= 3;
	static Opcode ADD 	= 4;
	static Opcode SUB 	= 5;
	static Opcode MUL	= 6;
	static Opcode DIV	= 7;

	static Opcode EXIT = 10;

}
/// vflags are used by the Compare instruction and are push on the stack to represent the result of the comparison
namespace vflags{
	typedef char flag;

	const static flag L		= 5;
	const static flag LE	= 4;
	const static flag G		= 3;
	const static flag GE	= 2;
	const static flag E		= 1;
	const static flag NE 	= 0;

}


#endif
