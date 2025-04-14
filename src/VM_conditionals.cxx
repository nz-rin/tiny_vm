
#include "Logger.hxx"

#include "Tiny_VM.hxx"

void VM::compare(){
	if(VM::stack_pointer < 2){
		log_error_and_exit("[ERROR] Stack underflow in \033[4mCOMPARE\033[0m");
	}
	vm_sword c1 = VM::stack_pop();
	vm_sword c2 = VM::stack_pop();
	VM::stack_push(c1-c2);
}


bool VM::check_condition(vm_sword cmp_res){
	if(VM::fr == vflags::E){
		return cmp_res == 0;
	}
	if(VM::fr == vflags::NE){
		return cmp_res != 0;
	}
	if(VM::fr == vflags::LE){
		return cmp_res <= 0;
	}
	if(VM::fr == vflags::L){
		return cmp_res < 0;
	}
	if(VM::fr == vflags::GE){
		return cmp_res >= 0;
	}
	if(VM::fr == vflags::G){
		return cmp_res > 0;
	}
	log_error_and_exit("Check conidtional failed, couldnt determine what flag is:", cmp_res );
	return false;
}

void VM::fjump(){
	VM::jr = VM::stack_pop();
	VM::fr = VM::stack_pop();

	switch(fr){
		case vflags::E:
			break;
		case vflags::NE:
			break;
		case vflags::LE:
			break;
		case vflags::L:
			break;
		case vflags::GE:
			break;
		case vflags::G:
			break;
		default:
			log_error_and_exit("[ERROR] Unkown Flag for \033[4mJump\033[0m", (int) fr);
	}

	vm_sword cmp_res = VM::stack_pop();
#ifdef DEBUG
	log_info("Compare res: ", cmp_res, "\nCheck Condition:", check_condition(cmp_res));
	log_info("Vflag:", (int)VM::fr);
#endif
	if (check_condition(cmp_res)){
		VM::inst_pointer = VM::jr;
	}
}

void VM::jump(){
#ifdef DEBUG
	auto a = VM::stack_pop();
	log_info("JUMPING TO:", a);
	VM::stack_push(a);
#endif
	VM::inst_pointer = VM::stack_pop();
}
