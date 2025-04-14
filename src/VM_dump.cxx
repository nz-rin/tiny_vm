
#include <iomanip>

#include "Logger.hxx"

#include "Tiny_VM.hxx"

void VM::dump_instructions(){
	log_info("[INSTRUCTION DUMP]");
	for(size_t i = 0; i < VM::memory_size; i++){
		log_info("[INST]", i, " ", (int) instructions[i]);
	}
}


#ifdef HEX_ADDR
	#define print_addr() std::cout << std::hex << '[' << addr << std::dec << ']' << '\t' ;
#else
	#define print_addr() std::cout << '[' << addr << std::dec << ']' << '\t' ;
#endif
void VM::dump_stack(){
	log_info("[STACK DUMP]");
	size_t bytes_to_dump = VM::stack_size;

	size_t addr = 0;
	while(bytes_to_dump > 8){
		print_addr();
		for( int i = 0; i < 8; i++, addr++)
			std::cout << ' ' << std::setw(8) << std::setfill('0') << (int) stack[addr+i];

		std::cout << '\n';

		bytes_to_dump -= 8;
	}
	print_addr();
	while(bytes_to_dump--){
		std::cout << ' ' << std::setw(8) << std::setfill('0') <<  (int) VM::stack[addr++];
	}
	std::cout << std::endl;
}
