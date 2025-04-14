
#include <stddef.h>

#include "Tiny_VM.hxx"
#include "Logger.hxx"

VM::VM(size_t memory_size, size_t stack_size){
	if(memory_size <= 0){
		log_error_and_exit("[ERROR] Virtual Machine Cannot be created with memory size 0 or less");
	}

	this->memory_size 	= memory_size;
	this->stack_size	= stack_size;

	instructions	= new vm_memory[memory_size];
	stack			= new vm_memory[stack_size];

	#ifdef DEBUG
		log_info("[Virtual Machine]");
		log_info("  Memory Size:", memory_size);
		log_info("  Memory ptr:", instructions);
		log_info("  Stack Size:", stack_size);
		log_info("  Stack ptr:", stack);
	#endif

}

VM::~VM(){
	#ifdef DEBUG
		log_info("[DESTRUCTOR] Cleaning up Virtual Machine\n[BEFORE]");
		log_info("  Memory ptr:", instructions);
		log_info("  Stack ptr:", stack);
	#endif

	delete[] instructions;
	delete[] stack;

	instructions	= nullptr;
	stack			= nullptr;
	#ifdef DEBUG
		log_info("[AFTER]");
		log_info("  Memory ptr:", instructions);
		log_info("  Stack ptr:", stack);
	#endif
}

void VM::run(){
	log_info("[RUNNING VIRTUAL MACHINE]");

	if(!VM::instructions_loaded){
		log_error_and_exit("[ERROR] Instructions are not present\nEnsure you loaded them before calling run.");
	}
	for(; VM::inst_pointer < VM::memory_size; VM::inst_pointer++)
		execute_instruction(VM::instructions[VM::inst_pointer], VM::inst_pointer, VM::instructions);
}
