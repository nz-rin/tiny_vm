
#include <vector>

#include "Logger.hxx"

#include "Tiny_VM.hxx"
#include "vlang.hxx"


void VM::load_instructions(std::vector<std::string> instructions){
	if(instructions.size() >= VM::memory_size){
		log_error("[WARNING] More Instructions Than Memory");
	}
	size_t i = 0;
	for(; i < instructions.size(); i++){
		VM::instructions[i] = std::atoll(instructions[i].c_str());
	}
	while(i < VM::memory_size){
		VM::instructions[i] = -1;
		i++;
	}
	VM::instructions_loaded = true;

}

void VM::execute_instruction(vasm::Opcode inst, vm_uword &ip, const vm_uword *instructions){
	switch(inst){
		case vasm::PUSH:{
#ifdef DEBUG
			log_info("[PUSH]", instructions[ip+1]);
#endif
			stack_push(instructions[++ip]);
		}
			break;

		case vasm::CMP:{
#ifdef DEBUG
			log_info("[CMP]");
#endif
			VM::compare();
		}
			break;

		case vasm::JMP:{
#ifdef DEBUG
			log_info("[JMP]");
#endif
			VM::jump();
		}
			break;

		case vasm::FJMP:{
#ifdef DEBUG
			log_info("[FJMP]");
#endif
			VM::fjump();
		}
			break;
		case vasm::ADD:{
#ifdef DEBUG
			log_info("[ADD]");
#endif

			VM::add();
		}
			break;


		case vasm::SUB:{
#ifdef DEBUG
			log_info("[SUB]");
#endif
			VM::sub();
		}
			break;

		case vasm::MUL:{
#ifdef DEBUG
			log_info("[SUB]");
#endif
			VM::mul();
		}
			break;
		case vasm::DIV:{
#ifdef DEBUG
			log_info("[SUB]");
#endif

			VM::div();
		}
			break;
		case vasm::EXIT:
#ifdef DEBUG
			log_info("[DONE]");
#endif
			ip=VM::memory_size+2;
			break;
		default:
			log_error("[ERROR] Unkown Opcode", inst);
	}

}
