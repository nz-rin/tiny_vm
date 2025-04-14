#include "Logger.hxx"

#include "Tiny_VM.hxx"

vm_sword VM::stack_pop(){
	if(VM::stack_pointer <= 0){
		log_error_and_exit("[ERROR] Stack Underflow in \033[4mPop\033[0m");
	}
	return (long) VM::stack[--stack_pointer];
}

void VM::stack_push(vm_uword data){
	if(VM::stack_pointer >= VM::stack_size){
		log_error_and_exit("[ERROR] Stack Overflow in \033[4mPush\033[0m");
	}
	VM::stack[stack_pointer++] = data;
}

