
#include "Logger.hxx"

#include "Tiny_VM.hxx"

/**
 * Pops two 64-BIT Integers of the Stack, adding their values together and
 * Pushes back a SIGNED 64-BIT Integer on the stack
 * Logs and error and exits if something goes wrong
 */
void VM::add(){
	if(VM::stack_pointer < 2){
		log_error_and_exit("[ERROR] Stack underflow in \033[4maddition\033[0m");
	}
	vm_sword lhs = static_cast<vm_sword>(VM::stack_pop());
	vm_sword rhs = static_cast<vm_sword>(VM::stack_pop());
	stack_push(lhs+rhs);
}

void VM::sub(){
	if(VM::stack_pointer < 2){
		log_error_and_exit("[ERROR] Stack underflow in \033[4msubtraction\033[0m");
	}
	vm_sword lhs = static_cast<vm_sword>(VM::stack_pop());
	vm_sword rhs = static_cast<vm_sword>(VM::stack_pop());
	stack_push(lhs-rhs);
}

void VM::mul(){
	if(VM::stack_pointer < 2){
		log_error_and_exit("[ERROR] Stack underflow in \033[4mmultiplication\033[0m");
	}
	vm_sword lhs = static_cast<vm_sword>(VM::stack_pop());
	vm_sword rhs = static_cast<vm_sword>(VM::stack_pop());
	stack_push(lhs*rhs);
}

void VM::div(){
	if(VM::stack_pointer < 2){
		log_error_and_exit("[ERROR] Stack underflow in \033[4mdivision\033[0m");
	}
	vm_sword lhs = static_cast<vm_sword>(VM::stack_pop());
	vm_sword rhs = static_cast<vm_sword>(VM::stack_pop());
	stack_push(lhs/rhs);
}

